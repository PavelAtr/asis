#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <errno.h>

ssize_t read(int f, void* buf, size_t count)
{
   if (!fd_is_valid(f)) {
      errno = BADFD;
      return -1;
   }
   return fread(buf, count, 1, fds[f].stream);
}
