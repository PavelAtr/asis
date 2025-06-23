/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

int dirfd(DIR *dirp)
{
   int fd = get_free_fd();
   if (fd == -1) {
      errno = ENOMEM;
      return -1;
   }
   afds[fd] = (FILE*) dirp;
   dirp->fd = fd;
   return fd;
}
