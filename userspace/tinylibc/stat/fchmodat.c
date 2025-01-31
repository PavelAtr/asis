#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int fchmodat(int f, const char *pathname, mode_t mode, int flags)
{
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   char* dir = (*fds)[f]->file;
   const char* file = pathname;
   if (pathname == NULL || flags & AT_EMPTY_PATH)
   {
      file = NULL;
   }
   if (flags & AT_FDCWD)
   {
      dir = get_current_dir_name();
   }
   struct stat st;
   char* path = fullpath(dir, file);
   if (stat(path, &st) == -1) {
      errno = ENOENT;
      return -1;
   }
   return syscall(SYS_MODNOD, path, st.st_uid, st.st_gid, mode);
}
