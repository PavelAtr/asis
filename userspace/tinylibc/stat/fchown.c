#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int fchown(int f, uid_t owner, gid_t group)
{
   INIT_FDS
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   struct stat st;
   if (stat(fds[f]->file, &st) == -1) {
      errno = ENOENT;
      return -1;
   }
   return syscall(SYS_MODNOD, fds[f]->file, owner, group, st.st_mode);
}

