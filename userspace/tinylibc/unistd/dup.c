#include <unistd.h>
#include <syscall.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int dup2(int oldfd, int newfd)
{
   if (!fd_is_valid(oldfd)) {
      errno = EBADFD;
      return -1;
   }
   if ((*fds)[newfd]) {
      close(newfd);
   }
   (*fds)[newfd] = calloc(1, sizeof(FILE));
   copyfile((*fds)[newfd], (*fds)[oldfd]);
   return newfd;
}

int dup(int oldfd) {
   int newfd;
   if ((newfd = get_free_fd()) != -1) {
      return dup2(oldfd, newfd);
   }
   errno = ENOMEM;
   return -1;
}
