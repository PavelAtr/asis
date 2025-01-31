#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int fstat(int f, struct stat *statbuf)
{
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   return syscall(SYS_FSTAT, (*fds)[f]->file, statbuf);
}

