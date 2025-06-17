#ifndef _SYS_TIMERFD_H
#define _SYS_TIMERFD_H

#include <fcntl.h>
#include <time.h>

#define TFD_TIMER_ABSTIME (1 << 0)
#define TFD_TIMER_CANCEL_ON_SET (1 << 1)
#define TFD_CLOEXEC O_CLOEXEC
#define TFD_NONBLOCK O_NONBLOCK

/* #define TFD_IOC_SET_TICKS	_IOW('T', 0, __u64) */

int timerfd_create(int clockid, int flags);
int timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value);
int timerfd_gettime(int fd, struct itimerspec *curr_value);

#endif
