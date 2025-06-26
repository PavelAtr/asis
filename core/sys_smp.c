#include <asis.h>
#undef printf
#include "../config.h"

#ifdef CONFIG_LINUX
#include <stdio.h>
#include <start.h>
#include <stdlib.h>
#endif

#ifdef CONFIG_UEFI
#include "uefi/uefi.h"
#endif


#define MAXCPU 4;

int maxcpu;
int newcpu = 0;
core** cpus;


void init_cpus()
{
    maxcpu = MAXCPU;
    cpus = malloc(sizeof(core*) * maxcpu);
    int i;
    for (i = 0; i < maxcpu; i++) {
        cpus[i] = calloc(1, sizeof(core));
        cpus[i]->startcycle = 1;
        cpus[i]->currentpid = 0;
    }
    printf("Init cpus\n");
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
            printf("FIND_STARTCYCLE CPU=%d PID=%d\n", cpunum, i);
            break;
        }
    }
}

int sys_runoncpu(startfunction start, startarg* arg, proc* task, int cpunum)
{
    task->cpunum = cpunum;
    find_startcycle(cpunum);
    int ret = start(arg);
    switch_context;
    return ret;
}

int sys_getcpu()
{
    int ret = newcpu;
    newcpu++;
    if (newcpu >= maxcpu)
        newcpu = 0;
    printf("SYS_GETCPU CPU=%d\n", ret);
    return ret;    
}

void sys_cpuidle(int cpu) {
    printf("CPU IDLE\n");
}

#ifndef CONFIG_UEFISMP
int schedcpu;
#endif

pid_t sys_endcycle(int cpunum) {
    find_startcycle(cpunum);
#ifdef CONFIG_UEFISMP
    return cpus[cpu]->startcycle;
#else
    schedcpu = cpunum;
    printf("SYS_ENDCYCLE START\n");
    while (1)
    {
        schedcpu++;
        if (schedcpu >= maxcpu) {
            schedcpu = 0;
        }
        sys_printf("NEWCPU=%d\n", schedcpu);
        if (schedcpu == cpunum) {
            sys_printf("NEW PID = 0\n");
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
            sys_printf("NEW PID = %d\n", newpid);
            return newpid;
        }
    }
    printf("SYS_ENDCYCLE\n");
    sys_printf("NEW PID = 0\n");
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