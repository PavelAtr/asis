#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

off_t lseek(int f, off_t offset, int whence)
{
   INIT_FDS
   if (fds[f]->flags & O_APPEND) {
      return fds[f]->pos;
   }
   return fseek(fds[f], offset, whence);
}
