#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int mkfifoat(int dirfd, const char *pathname, mode_t mode)
{
   INIT_afds
   if (!fd_is_valid(dirfd)) {
      errno = EBADFD;
      return -1;
   }
   char* dir = afds[dirfd]->file;
   return mkfifo(pathname, mode); /* BUG NOT REALIZED */
}
