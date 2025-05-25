#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#include <signal.h>
#include <time.h>

typedef unsigned long fd_mask;
#define FD_SETSIZE 1024
#define NFDBITS (8 * sizeof(fd_mask))
typedef struct {
  fd_mask fds_bits[FD_SETSIZE/NFDBITS];
} fd_set;

int select(int nfds, fd_set *  readfds,
          fd_set *  writefds,
          fd_set *  exceptfds,
          struct timeval *  timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

int pselect(int nfds, fd_set *  readfds,
     fd_set *  writefds,
     fd_set *  exceptfds,
     const struct timespec *  timeout,
     const sigset_t *  sigmask);

#endif