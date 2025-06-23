#include <asis.h>
#include <start.h>

#define MAXCPU 8;

int maxcpu;
int curcpu = 0;

void init_cpus()
{
    maxcpu = MAXCPU;
}

pid_t find_startcycle(int cpunum)
{
    pid_t i;
    for (i = 0; i < MAXPROC; i++)
    {
        if (cpu[i]->cpunum == cpunum)
            return i;
    }
    return -1;
}

int sys_runoncpu(startfunction start, startarg* arg, proc* task, int cpunum)
{
    task->cpunum = cpunum;
    int ret = start(arg);
    switch_context;
    return ret;
}

int sys_getcpu()
{
    curcpu++;
    if (curcpu > maxcpu)
        curcpu = 0;
    return curcpu;    
}