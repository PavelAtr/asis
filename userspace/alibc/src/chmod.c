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
   const char* file =  strdup(pathname);
   if (stat(file, &st) == -1) {
      errno = ENOENT;
      return -1;
   }
   return (int)asyscall(SYS_MODNOD, file, st.st_uid, st.st_gid, mode, 0, 0);
}