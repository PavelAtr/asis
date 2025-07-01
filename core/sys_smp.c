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
#endif

int_t maxcpu;
int_t newcpu = 0;
core** cpus;


#ifndef CONFIG_UEFISMP
int schedcpu = 0;
#endif

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

int sys_runoncpu(startfunction start, proc* task, int cpunum)
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

#ifndef CONFIG_UEFISMP
    schedcpu = cpunum;
    int ret = start(&arg);
#endif
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
    find_startcycle(cpunum);
#ifdef CONFIG_UEFISMP
    return cpus[cpu]->startcycle;
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