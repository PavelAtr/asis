#include <unistd.h>
#include <syscall.h>
#include <tiny.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int ftruncate(int f, off_t length)
{
   INIT_afds
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   size_t outsize = length;
   FILE* stream = afds[f];
   if (stream->type & F_NAMEDMEM)
   {
      if ((errno = (int)asyscall(SYS_SHARED, &((amemfile*)stream)->membuf, "memfd", stream->file, "", &outsize, 0)))
      {
          return -1;   
      }
      stream->size = (stream->size < outsize)? outsize : stream->size;
      return 0;
   }
   return (int)asyscall(SYS_TRUNCATE, afds[f]->file, length, 0, 0, 0, 0);
}