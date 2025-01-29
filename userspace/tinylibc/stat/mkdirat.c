#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int mkdirat(int f, const char *pathname, mode_t mode)
{
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   char* dir = fds[f]->file;
   return mkdir(fullpath(dir, pathname), mode);
}
