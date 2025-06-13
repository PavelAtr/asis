#include <stdio.h>
#include <fcntl.h>

FILE *fdopen(int fd, const char *mode)
{
   INIT_afds
   if (!fd_is_valid(fd)) {
      return NULL;
   }
   return afds[fd];
}
