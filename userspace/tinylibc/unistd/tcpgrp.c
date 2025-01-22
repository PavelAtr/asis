#include <unistd.h>
#include <syscall.h>
#include <fcntl.h>
#include <errno.h>


pid_t tcgetpgrp(int fd)
{
   if (!fd_is_valid(fd) || !fds[fd].stream->file) {
      errno = EBADFD;
      return -1;
   }
   pid_t ret = (fds[fd].pgrp)? 100 : fds[fd].pgrp;
   return ret;
}

int tcsetpgrp(int fd, pid_t pgrp)
{
   if (!fd_is_valid(fd) || !fds[fd].stream->file) {
      errno = EBADFD;
      return -1;
   }
   fds[fd].pgrp = pgrp;
   return 0;
}
