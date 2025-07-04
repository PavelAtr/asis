#include <syscall.h>
#include <sys/stat.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int chmod(const char *pathname, mode_t mode)
{
   struct stat st;
   if (stat(pathname, &st) == -1) {
      errno = ENOENT;
      return -1;
   }
   mode_t fmt = st.st_mode & S_IFMT;
   if ((errno = (int)asyscall(SYS_MODNOD, pathname, st.st_uid, st.st_gid, fmt | mode, 0, 0))) {
      return -1;
   }
   return 0;
}