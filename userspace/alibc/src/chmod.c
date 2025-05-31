#include <syscall.h>
#include <sys/stat.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int chmod(const char *pathname, mode_t mode)
{
   struct stat st;
   char* file = fullpath(get_current_dir_name(), pathname);
   if (stat(file, &st) == -1) {
      errno = ENOENT;
      return -1;
   }
   return asyscall(SYS_MODNOD, file, st.st_uid, st.st_gid, mode, 0, 0);
}