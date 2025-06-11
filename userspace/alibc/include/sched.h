#ifndef _SYS_SCHED_H
#define _SYS_SCHED_H

static inline int unshare(int flags)
{
    return 0;
}

#define CLONE_FILES 1
#define CLONE_FS 2
#define CLONE_NEWCGROUP 3
#define CLONE_NEWIPC 4
#define CLONE_NEWNET 5
#define CLONE_NEWNS 6
#define CLONE_NEWPID 7
#define CLONE_NEWTIME 8
#define CLONE_NEWUSER 9
#define CLONE_NEWUTS 10
#define CLONE_SYSVSEM 11

#endif