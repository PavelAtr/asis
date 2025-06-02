#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int fstat(int f, struct stat *statbuf)
{
   INIT_FDS
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   return (int)asyscall(SYS_FSTAT, fds[f]->file, statbuf, 0, 0, 0, 0);
}

