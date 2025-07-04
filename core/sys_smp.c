#include <asis.h>
#undef printf
#undef free
#include "../config.h"

#ifdef CONFIG_LINUX
#include <stdio.h>
#include <start.h>
#endif

#ifdef CONFIG_UEFI
#include "uefi/uefi.h"
#include "uefi_smp.h"
#endif

int_t maxcpu;
int_t newcpu = 0;
core** cpus;

#ifdef CONFIG_UEFISMP
    efi_mp_services_t *MpServices;
    efi_guid_t gEfiMpServiceProtocolGuid = EFI_MP_SERVICES_PROTOCOL_GUID;
#else
    int schedcpu = 0;
#endif

void init_cores(void)
{
#ifdef CONFIG_UEFISMP
    efi_status_t Status = BS->LocateProtocol(&gEfiMpServiceProtocolGuid, NULL, (void**)&MpServices);
    unsigned long NumberOfProcessors, NumberOfEnabledProcessors = 0;
    if (!EFI_ERROR(Status)) {
        MpServices->GetNumberOfProcessors(MpServices, &NumberOfProcessors, &NumberOfEnabledProcessors);
    } else {
        sys_printf(SYS_ERROR "Error detecting cores %p\n", Status);
    }
    maxcpu = (int_t)NumberOfEnabledProcessors;
#else
    maxcpu = MAXCPU;
#endif
    sys_printf(SYS_INFO "Init cores: %d enabled core\n", maxcpu);
}

void find_startcycle(int cpunum)
{
    pid_t i;
    for (i = 1; i < MAXPROC; i++)
    {
        if (!cpu[i])
            continue;
        if (cpu[i]->cpunum == cpunum && !(cpu[i]->flags & PROC_ENDED))
        {
            cpus[cpunum]->startcycle = i;
//            printf("FIND_STARTCYCLE CPU=%d PID=%d\n", cpunum, i);
            break;
        }
    }
}

int sys_runtask(startfunction start, proc* task, int cpunum)
{
    startarg arg;
    arg.argc = task->argc;
    arg.cargv = task->argv;
    arg.cenvp = task->envp;
    arg.cfds = task->fds;
    arg.syscall_func = &sys_syscall;
    arg.retexit_func = &sys_atexit;
    task->cpunum = cpunum;
    find_startcycle(cpunum);
    cpus[cpunum]->currentpid = task->pid;
    switch_context;
    int ret = start(&arg);
    switch_context;
    return ret;
}

int sys_getcpu()
{
    int ret = newcpu;
    newcpu++;
    if (newcpu >= maxcpu)
        newcpu = 0;
//    printf("SYS_GETCPU CPU=%d\n", ret);
    return ret;    
}

void sys_cpuidle(int cpu) {
//    printf("CPU IDLE\n");
}

pid_t sys_endcycle(int cpunum) {
    sys_printf(SYS_DEBUG "ENDCYCLE CPU=%d PID=%d\n", cpunum, cpus[cpunum]->startcycle);    
    find_startcycle(cpunum);
#ifdef CONFIG_UEFISMP
    return cpus[cpunum]->startcycle;
#else
    schedcpu = cpunum;
//    printf("SYS_ENDCYCLE START\n");
    while (1)
    {
        schedcpu++;
        if (schedcpu >= maxcpu) {
            schedcpu = 0;
        }
//        sys_printf("NEWCPU=%d\n", schedcpu);
        if (schedcpu == cpunum) {
//            sys_printf("NEW PID = 0\n");
            return 0;
        }
        find_startcycle(schedcpu);
        pid_t newpid;
        for (newpid = cpus[schedcpu]->startcycle; newpid < MAXPROC; newpid++)
        {
            if (!cpu[newpid]) {
                continue;
            }
            if (!(cpu[newpid]->flags & PROC_RUNNING)) {
                continue;
            }
            if (cpu[newpid]->cpunum != schedcpu) {
                continue;
            }
//            sys_printf("NEW PID = %d\n", newpid);
            return newpid;
        }
    }
//    printf("SYS_ENDCYCLE\n");
//    sys_printf("NEW PID = 0\n");
    return 0;
#endif
}

int sys_current_cpu()
{
#ifdef CONFIG_UEFISMP
    return 0;
#else
    return schedcpu;
#endif
}