#include <stdio.h>
#include <fcntl.h>
#include <syscall.h>

FILE *fdopen(int fd, const char *mode)
{
   if (!fd_is_valid(fd)) {
      return NULL;
   }
   if (fds[fd]->stream) {
      return fds[fd]->stream;
   }
   return NULL;
}
