#ifndef _SYS_WAIT_H
#define _SYS_WAIT_H

#include <sys/types.h>

#define WNOHANG         0x00000001
#define WUNTRACED       0x00000002
#define WSTOPPED        WUNTRACED
#define WEXITED         0x00000004
#define WCONTINUED      0x00000008
#define WNOWAIT         0x01000000      /* Don't reap, just poll status.  */

/* First argument to waitid: */
#define P_ALL           0
#define P_PID           1
#define P_PGID          2
#define P_PIDFD         3




#define WEXITSTATUS(status)   (((status) & 0xff00) >> 8)
#define WTERMSIG(status)      ((status) & 0x7f)
#define WSTOPSIG(status)      WEXITSTATUS(status)
#define WIFEXITED(status)     (WTERMSIG(status) == 0)
#define WIFSIGNALED(status) \
  (((signed char) (((status) & 0x7f) + 1) >> 1) > 0)
#define WIFSTOPPED(status)    (((status) & 0xff) == 0x7f)
#ifdef WCONTINUED
# define WIFCONTINUED(status) ((status) == W_CONTINUED)
#endif
#define WCOREDUMP(status)     ((status) & WCOREFLAG)
#define W_EXITCODE(ret, sig)  ((ret) << 8 | (sig))
#define W_STOPCODE(sig)       ((sig) << 8 | 0x7f)
#define W_CONTINUED           0xffff
#define WCOREFLAG             0x80


pid_t waitpid(pid_t pid, int* wstatus, int options);
pid_t wait(int* wstatus);
pid_t wait3(int* wstatus, int options, void* rusage);



#endif
