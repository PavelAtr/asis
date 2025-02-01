#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <syscall.h>
#include <stdlib.h>
#include <errno.h>

int close(int fd)
{
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   freefile(fds[fd]);
   fds[fd] = NULL;
   return 0;
}
