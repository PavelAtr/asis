#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

ssize_t write(int f, const void* buf, size_t count)
{
   INIT_afds
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   return fwrite(buf, 1, count, afds[f]);
}
