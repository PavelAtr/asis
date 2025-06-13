#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

off_t lseek(int f, off_t offset, int whence)
{
   INIT_afds
   if (afds[f]->flags & O_APPEND) {
      return afds[f]->pos;
   }
   return fseek(afds[f], offset, whence);
}
