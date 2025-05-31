#include <stdio.h>
#include <fcntl.h>

FILE *fdopen(int fd, const char *mode)
{
   INIT_FDS
   if (!fd_is_valid(fd)) {
      return NULL;
   }
   return fds[fd];
}
