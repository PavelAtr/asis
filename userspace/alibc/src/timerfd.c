#include <stdio.h>
#include <sys/timerfd.h>

#include <sys/timerfd.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int timerfd_create(int clockid, int flags) {
   INIT_afds
   int fd = get_free_fd();
   if (fd == -1) {
      errno = ENOMEM;
      return -1;
   }
   afds[fd] = (FILE*)calloc(1, sizeof(aeventfd));
   if (!afds[fd]) {
      errno = ENOMEM;
      return -1;
   }
   ((atimerfd*)afds[fd])->flags = flags;
   return fd;
}

int timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value) {
   INIT_afds
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
    if (old_value)
        *old_value = ((atimerfd*)afds[fd])->spec;
  ((atimerfd*)afds[fd])->spec = *new_value;
    clock_gettime(CLOCK_REALTIME, &((atimerfd*)afds[fd])->next_expiry);
    ((atimerfd*)afds[fd])->next_expiry.tv_sec += new_value->it_value.tv_sec;
    ((atimerfd*)afds[fd])->next_expiry.tv_nsec += new_value->it_value.tv_nsec;
    if (((atimerfd*)afds[fd])->next_expiry.tv_nsec >= 1000000000) {
        ((atimerfd*)afds[fd])->next_expiry.tv_sec += 1;
        ((atimerfd*)afds[fd])->next_expiry.tv_nsec -= 1000000000;
    }
    ((atimerfd*)afds[fd])->expirations = 0;
    return 0;
}

int timerfd_gettime(int fd, struct itimerspec *curr_value) {
   INIT_afds
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
    if (curr_value)
        *curr_value = ((atimerfd*)afds[fd])->spec;
    return 0;
}