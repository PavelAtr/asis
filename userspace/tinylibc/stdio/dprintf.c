#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <syscall.h>

int dprintf(int fd, const char* format, ...)
{
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   va_list args;
   int n;
   va_start(args, format);
   n = vfprintf(fds[fd]->stream, format, args);
   va_end(args);
   return n;
}
