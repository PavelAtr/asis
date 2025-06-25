#include <asis.h>
#undef printf
#include <stdio.h>
#include <start.h>
#include <stdlib.h>
#include "../config.h"

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

#ifdef CONFIG_LINUX
int schedcpu;
#endif

pid_t sys_endcycle(int cpunum) {
    find_startcycle(cpunum);
    #ifdef CONFIG_UEFI
    return cpus[cpu]->startcycle;
    #endif
    #ifdef CONFIG_LINUX
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
    return 0;
    #endif
}

int sys_current_cpu()
{
#ifdef CONFIG_LINUX
    return schedcpu;
#endif
    return 0;
}