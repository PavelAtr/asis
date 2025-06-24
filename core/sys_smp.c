#include <asis.h>
#undef printf
#include <stdio.h>
#include <start.h>
#include <stdlib.h>
#include "../config.h"

#define MAXCPU 4;

int maxcpu;
int curcpu = 0;
core** cpus;


void init_cpus()
{
    maxcpu = MAXCPU;
    cpus = malloc(sizeof(core*) * maxcpu);
    int i;
    for (i = 0; i < maxcpu; i++) {
        cpus[i] = calloc(1, sizeof(core));
        cpus[i]->startcycle = 1;
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
    int ret = curcpu;
    curcpu++;
    if (curcpu >= maxcpu)
        curcpu = 0;
    printf("SYS_GETCPU CPU=%d\n", ret);
    return ret;    
}

void sys_cpuidle(int cpu) {
    printf("CPU IDLE\n");
}

pid_t sys_endcycle(int cpunum) {
    find_startcycle(cpunum);
    #ifdef CONFIG_UEFI
    return cpus[cpu]->startcycle;
    #endif
    #ifdef CONFIG_LINUX
    int newcpu = cpunum;
    printf("SYS_ENDCYCLE START\n");
    while (1)
    {
        newcpu++;
        if (newcpu >= maxcpu) {
            newcpu = 0;
        }
        sys_printf("NEWCPU=%d\n", newcpu);
        if (newcpu == cpunum) {
            return 0;
        }
        find_startcycle(newcpu);
        pid_t newpid;
        for (newpid = cpus[newcpu]->startcycle; newpid < MAXPROC; newpid++)
        {
            if (!cpu[newpid]) {
                continue;
            }
            if (!(cpu[newpid]->flags & PROC_RUNNING)) {
                continue;
            }
            if (cpu[newpid]->cpunum != newcpu) {
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