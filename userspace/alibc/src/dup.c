#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int dup2(int oldfd, int newfd)
{
   INIT_FDS
   if (!fd_is_valid(oldfd)) {
      errno = EBADFD;
      return -1;
   }
   if (fds[newfd]) {
      close(newfd);
   }
   fds[newfd] = malloc(sizeof(FILE));
   copyfile(fds[newfd], fds[oldfd]);
   fds[newfd]->fd = newfd;
   return newfd;
}

int dup(int oldfd) {
   INIT_FDS
   int newfd;
   if ((newfd = get_free_fd()) != -1) {
      return dup2(oldfd, newfd);
   }
   errno = ENOMEM;
   return -1;
}
