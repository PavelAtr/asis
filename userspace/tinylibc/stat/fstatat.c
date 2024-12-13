#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int fstatat(int f, const char* pathname,
                struct stat* statbuf, int flags)
{
   if (!fd_is_valid(f)) {
      errno = BADFD;
      return -1;
   }
   char* file = pathname;
   if (pathname == NULL || flags & AT_EMPTY_PATH)
   {
      file = NULL;
   }
   return syscall(SYS_FSTAT, fullpath(fds[f].stream->file, file), statbuf);
}
