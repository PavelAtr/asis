#ifndef _TIME_H
#define _TIME_H

#include <sys/types.h>
#include <sys/time.h>

struct timespec {
   time_t     tv_sec;   /* Seconds */
   time_t  tv_nsec;  /* Nanoseconds [0, 999'999'999] */
};

struct itimerspec {
        struct timespec it_interval;/* timer period */
        struct timespec it_value;       /* timer expiration */
};

struct itimerval {
        struct timeval it_interval;/* timer interval */
        struct timeval it_value;        /* current value */
};

int nanosleep(const struct timespec *req, struct timespec* rem);

#endif