#ifndef _SIGNAL_H
#define _SIGNAL_H

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

#endif