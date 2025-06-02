#include <unistd.h>
#include <syscall.h>
#include <tiny.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int ftruncate(int f, off_t length)
{
   INIT_FDS
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }

   return (int)asyscall(SYS_TRUNCATE, fds[f]->file, length, 0, 0, 0, 0);
}