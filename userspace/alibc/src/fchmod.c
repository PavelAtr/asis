#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int fchmod(int f, mode_t mode)
{
   INIT_afds
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   struct stat st;
   if (stat(afds[f]->file, &st) == -1) {
      errno = ENOENT;
      return -1;
   }
   return (int)asyscall(SYS_MODNOD, afds[f]->file, st.st_uid, st.st_gid, mode, 0, 0);
}

