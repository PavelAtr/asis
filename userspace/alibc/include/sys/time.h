#ifndef _SYS_TIME_H
#define _SYS_TIME_H

#include <sys/types.h>

struct timezone {
   int     tz_minuteswest; /* minutes west of Greenwich */
   int     tz_dsttime;     /* type of dst correction */
};

struct timeval {
   time_t       tv_sec;   /* Seconds */
   suseconds_t  tv_usec;  /* Microseconds */
};

int gettimeofday(struct timeval* tv, struct timezone* tz);
int settimeofday(const struct timeval *tv, const struct timezone* tz);
int futimes(int fd, const struct timeval tv[2]);
int futimesat(int dirfd, const char *pathname,
                const struct timeval times[2]);
int lutimes(const char *filename, const struct timeval tv[2]);

#endif
