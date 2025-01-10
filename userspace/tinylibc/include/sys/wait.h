#ifndef _WAIT_H
#define _WAIT_H

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


#endif
