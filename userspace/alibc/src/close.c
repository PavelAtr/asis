#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>

int close(int fd)
{
   INIT_afds
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   afds[fd]->fd = -1;
   fclose(afds[fd]);
   afds[fd] = NULL;
   return 0;
}
