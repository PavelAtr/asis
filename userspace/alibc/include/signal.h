#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/types.h>
#include <pthreadtypes.h>

typedef unsigned long sigset_t;

int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
int sigismember(const sigset_t *set, int signum);
int sigprocmask(int how, const sigset_t* set, sigset_t* oldset);
/* Values for the HOW argument to `sigprocmask'.  */
#define SIG_BLOCK     0          /* Block signals.  */
#define SIG_UNBLOCK   1          /* Unblock signals.  */
#define SIG_SETMASK   2          /* Set the set of blocked signals.  */

union sigval {
  int     sigval_int; /* Integer value */
  void   *sigval_ptr; /* Pointer value */
};

struct sigevent {
  int             sigev_notify; /* Notification type */
  int             sigev_signo;  /* Signal number */
  union sigval    sigev_value;  /* Signal value */
  void          (*sigev_notify_function)(union sigval);
                       /* Notification function */
  pthread_attr_t *sigev_notify_attributes;
                    /* Notification attributes */
};

typedef struct {
  int      si_signo;  /* Signal number */
  int      si_code;   /* Signal code */
  pid_t    si_pid;    /* Sending process ID */
  uid_t    si_uid;    /* Real user ID of sending process */
  void    *si_addr;   /* Address of faulting instruction */
  int      si_status; /* Exit value or signal */
  union sigval si_value;  /* Signal value */
} siginfo_t;

typedef void (*__sighandler_t) (int);

#define SIG_DFL ((__sighandler_t)0)     /* default signal handling */
#define SIG_IGN ((__sighandler_t)1)     /* ignore signal */
#define SIG_ERR ((__sighandler_t)-1)    /* error return from signal */

#define _NSIG           64
#define NSIG           _NSIG
#define _NSIG_BPW       __BITS_PER_LONG
#define _NSIG_WORDS     (_NSIG / _NSIG_BPW)

#define SIGHUP           1
#define SIGINT           2
#define SIGQUIT          3
#define SIGILL           4
#define SIGTRAP          5
#define SIGABRT          6
#define SIGIOT           6
#define SIGBUS           7
#define SIGFPE           8
#define SIGKILL          9
#define SIGUSR1         10
#define SIGSEGV         11
#define SIGUSR2         12
#define SIGPIPE         13
#define SIGALRM         14
#define SIGTERM         15
#define SIGSTKFLT       16
#define SIGCHLD         17
#define SIGCONT         18
#define SIGSTOP         19
#define SIGTSTP         20
#define SIGTTIN         21
#define SIGTTOU         22
#define SIGURG          23
#define SIGXCPU         24
#define SIGXFSZ         25
#define SIGVTALRM       26
#define SIGPROF         27
#define SIGWINCH        28
#define SIGIO           29
#define SIGPOLL         SIGIO
/*
#define SIGLOST         29
*/
#define SIGPWR          30
#define SIGSYS          31
#define SIGUNUSED       31

/* These should not be considered constants from userland.  */
#define SIGRTMIN        32
#ifndef SIGRTMAX
#define SIGRTMAX        _NSIG
#endif

struct sigaction {
  void     (*sa_handler)(int);
  void     (*sa_sigaction)(int, siginfo_t *, void *);
  sigset_t   sa_mask;
  int        sa_flags;
  void     (*sa_restorer)(void);
};

int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact);
int kill(pid_t pid, int sig);

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
int raise(int sig);
int sigsuspend(const sigset_t *mask);
int sigsetmask(int mask);
int killpg(int pgrp, int sig);

int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);

#ifndef SA_NOCLDSTOP
#define SA_NOCLDSTOP    0x00000001
#endif
#ifndef SA_NOCLDWAIT
#define SA_NOCLDWAIT    0x00000002
#endif
#ifndef SA_SIGINFO
#define SA_SIGINFO      0x00000004
#endif
/* 0x00000008 used on alpha, mips, parisc */
/* 0x00000010 used on alpha, parisc */
/* 0x00000020 used on alpha, parisc, sparc */
/* 0x00000040 used on alpha, parisc */
/* 0x00000080 used on parisc */
/* 0x00000100 used on sparc */
/* 0x00000200 used on sparc */
#define SA_UNSUPPORTED  0x00000400
#define SA_EXPOSE_TAGBITS       0x00000800
/* 0x00010000 used on mips */
/* 0x00800000 used for internal SA_IMMUTABLE */
/* 0x01000000 used on x86 */
/* 0x02000000 used on x86 */
/*
 * New architectures should not define the obsolete
 *      SA_RESTORER     0x04000000
 */
#ifndef SA_ONSTACK
#define SA_ONSTACK      0x08000000
#endif
#ifndef SA_RESTART
#define SA_RESTART      0x10000000
#endif
#ifndef SA_NODEFER
#define SA_NODEFER      0x40000000
#endif
#ifndef SA_RESETHAND
#define SA_RESETHAND    0x80000000
#endif

#define SA_NOMASK       SA_NODEFER
#define SA_ONESHOT      SA_RESETHAND

#ifndef SIG_BLOCK
#define SIG_BLOCK          0    /* for blocking signals */
#endif
#ifndef SIG_UNBLOCK
#define SIG_UNBLOCK        1    /* for unblocking signals */
#endif
#ifndef SIG_SETMASK
#define SIG_SETMASK        2    /* for setting the signal mask */
#endif

#ifndef __ASSEMBLY__
typedef void __signalfn_t(int);
typedef __signalfn_t *__sighandler_t;

typedef void __restorefn_t(void);
typedef __restorefn_t *__sigrestore_t;

#define SIG_DFL ((__sighandler_t)0)     /* default signal handling */
#define SIG_IGN ((__sighandler_t)1)     /* ignore signal */
#define SIG_ERR ((__sighandler_t)-1)    /* error return from signal */
#endif


#endif
