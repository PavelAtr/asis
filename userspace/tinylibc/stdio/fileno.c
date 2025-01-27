#include <stdio.h>
#include <fcntl.h>
#include <syscall.h>
#include <errno.h>

int fileno(FILE *stream)
{
   int i;
   for (i = 0; i < syscall(SYS_GETMAXFD); i++) {
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