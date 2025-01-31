#include <syscall.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>

DIR *fdopendir(int fd)
{
   if (!fd_is_valid(fd)) {
      return NULL;
   }
   return opendir((*fds)[fd]->file);
}
