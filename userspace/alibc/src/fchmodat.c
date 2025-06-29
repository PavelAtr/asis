#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int fchmodat(int f, const char *pathname, mode_t mode, int flags)
{
   INIT_afds
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   char* dir = afds[f]->file;
   char* file = strdup(pathname);
   if (pathname == NULL || flags & AT_EMPTY_PATH)
   {
      file = strdup("");
   }
   if (flags & AT_FDCWD)
   {
      dir = get_current_dir_name();
   }
   struct stat st;
   char* path = file; /* BUG NOT REALIZED */
   if (stat(path, &st) == -1) {
      errno = ENOENT;
      return -1;
   }
   return (int)asyscall(SYS_MODNOD, path, st.st_uid, st.st_gid, mode, 0, 0);
}
