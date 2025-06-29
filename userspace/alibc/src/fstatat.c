#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int fstatat(int f, const char* pathname,
                struct stat* statbuf, int flags)
{
   INIT_afds
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   if (pathname == NULL || flags & AT_EMPTY_PATH)
   {
      pathname = "";
   }
   char* dir = afds[f]->file;
   if (flags & AT_FDCWD)
   {
      dir = get_current_dir_name();
   }
   char* file;
   splitpath(file, dir, pathname);
   int ret = (int)asyscall(SYS_FSTAT, file, statbuf, 0, 0, 0, 0);
   if (flags & AT_FDCWD)
   {
      free(dir);
   }
   return  ret;
}
