#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>


ssize_t pread(int f, void* buf, size_t count, off_t offset)
{
   INIT_afds
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   size_t ret;
   off_t old = ftell(afds[f]);
   fseek(afds[f], SEEK_SET, offset);
   ret = fread(buf, 1, count, afds[f]);
   fseek(afds[f], SEEK_SET, old);
   return ret;
}
