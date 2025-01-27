#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int fchown(int f, uid_t owner, gid_t group)
{
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   struct stat st;
   if (stat(fds[f]->stream->file, &st) == -1) {
      errno = ENOENT;
      return -1;
   }
   return syscall(SYS_MODNOD, fds[f]->stream->file, owner, group, st.st_mode);
}

