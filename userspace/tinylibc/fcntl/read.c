#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


ssize_t read(int f, void* buf, size_t count)
{
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   return fread(buf, 1, count, fds[f]->stream);
}
