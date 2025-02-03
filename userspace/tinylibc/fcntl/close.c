#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <syscall.h>
#include <stdlib.h>
#include <errno.h>

int close(int fd)
{
   INIT_FDS
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   fds[fd]->fd = -1;
   fclose(fds[fd]);
   fds[fd] = NULL;
   return 0;
}
