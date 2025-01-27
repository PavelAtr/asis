#include <stdio.h>
#include <fcntl.h>
#include <syscall.h>
#include <errno.h>

int fileno(FILE *stream)
{
   int i;
   for (i = 0; i < MAXFD; i++) {
      if (!fds[i]) {
         continue;
      }
      if (fds[i]->stream == stream) {
         return i;
      }
   }
   errno = EBADFD;
   return -1;
}