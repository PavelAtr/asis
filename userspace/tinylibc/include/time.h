#ifndef _TIME_H
#define _TIME_H

#include <sys/types.h>
#include <sys/time.h>

struct timespec {
   time_t     tv_sec;   /* Seconds */
   time_t  tv_nsec;  /* Nanoseconds [0, 999'999'999] */
};

#endif