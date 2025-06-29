#include <sys/select.h>

/* NOT REALIZED */

int select(int nfds, fd_set *  readfds,
          fd_set *  writefds,
          fd_set *  exceptfds,
          struct timeval *  timeout)
{
   return 0;
}

void FD_CLR(int fd, fd_set *set) {}

int  FD_ISSET(int fd, fd_set *set)
{
  return 0;
}

void FD_SET(int fd, fd_set *set) {}

void FD_ZERO(fd_set *set) {}

int pselect(int nfds, fd_set *  readfds,
     fd_set *  writefds,
     fd_set *  exceptfds,
     const struct timespec *  timeout,
     const sigset_t *  sigmask)
{
  return 0;
}

