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


#endif