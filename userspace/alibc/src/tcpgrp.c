#include <unistd.h>
#include <syscall.h>
#include <fcntl.h>
#include <errno.h>


pid_t tcgetpgrp(int fd)
{
   INIT_afds
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   pid_t ret = (afds[fd]->pgrp)? 100 : afds[fd]->pgrp;
   return ret;
}

int tcsetpgrp(int fd, pid_t pgrp)
{
   INIT_afds
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   afds[fd]->pgrp = pgrp;
   return 0;
}
