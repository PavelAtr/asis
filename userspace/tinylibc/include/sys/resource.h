#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H

#include <sys/types.h>
#include <time.h>

#define RUSAGE_SELF     0
#define RUSAGE_CHILDREN (-1)
#define RUSAGE_BOTH     (-2)            /* sys_wait4() uses this */
#define RUSAGE_THREAD   1               /* only the calling thread */

struct  rusage {
        struct timeval ru_utime;   /* user time used */
        struct timeval ru_stime;   /* system time used */
        long_t ru_maxrss;      /* maximum resident set size */
        long_t ru_ixrss;       /* integral shared memory size */
        long_t ru_idrss;       /* integral unshared data size */
        long_t ru_isrss;       /* integral unshared stack size */
        long_t ru_minflt;      /* page reclaims */
        long_t ru_majflt;      /* page faults */
        long_t ru_nswap;       /* swaps */
        long_t ru_inblock;     /* block input operations */
        long_t ru_oublock;     /* block output operations */
        long_t ru_msgsnd;      /* messages sent */
        long_t ru_msgrcv;      /* messages received */
        long_t ru_nsignals;    /* signals received */
        long_t ru_nvcsw;       /* voluntary context switches */
        long_t ru_nivcsw;      /* involuntary " */
};

struct rlimit {
        ulong_t        rlim_cur;
        ulong_t        rlim_max;
};

#define RLIM64_INFINITY         (~0ULL)

struct rlimit64 {
        unsigned long long rlim_cur;
        unsigned long long rlim_max;
};

#define PRIO_MIN        (-20)
#define PRIO_MAX        20

#define PRIO_PROCESS    0
#define PRIO_PGRP       1
#define PRIO_USER       2

#define RLIM_INFINITY          (~0UL)

int getrlimit(int resource, struct rlimit *rlim);
int setrlimit(int resource, const struct rlimit *rlim);

#endif
