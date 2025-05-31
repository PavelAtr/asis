#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>

int dprintf(int fd, const char* format, ...)
{
   INIT_FDS
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   va_list args;
   int n;
   va_start(args, format);
   n = vfprintf(fds[fd], format, args);
   va_end(args);
   return n;
}
