#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#include <signal.h>
#include <time.h>

#ifndef FD_SETSIZE
#define FD_SETSIZE 1024
#endif

typedef struct {
    unsigned long fds_bits[(FD_SETSIZE + (8 * sizeof(unsigned long) - 1)) / (8 * sizeof(unsigned long))];
} fd_set;

typedef unsigned long fd_mask;

int select(int nfds, fd_set *  readfds,
          fd_set *  writefds,
          fd_set *  exceptfds,
          struct timeval *  timeout);


#define FD_ZERO(set) \
    do { \
        size_t __i; \
        for (__i = 0; __i < sizeof(fd_set)/sizeof(unsigned long); ++__i) \
            (set)->fds_bits[__i] = 0; \
    } while (0)

#define FD_SET(fd, set) \
    ((set)->fds_bits[(fd) / (8 * sizeof(unsigned long))] |= (1UL << ((fd) % (8 * sizeof(unsigned long)))))

#define FD_CLR(fd, set) \
    ((set)->fds_bits[(fd) / (8 * sizeof(unsigned long))] &= ~(1UL << ((fd) % (8 * sizeof(unsigned long)))))

#define FD_ISSET(fd, set) \
    (((set)->fds_bits[(fd) / (8 * sizeof(unsigned long))] & (1UL << ((fd) % (8 * sizeof(unsigned long))))) != 0)

int pselect(int nfds, fd_set *  readfds,
     fd_set *  writefds,
     fd_set *  exceptfds,
     const struct timespec *  timeout,
     const sigset_t *  sigmask);

#endif