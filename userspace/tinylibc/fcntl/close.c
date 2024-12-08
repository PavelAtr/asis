#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <syscall.h>
#include <stdlib.h>

int close(int fd)
{
   if (!fd_is_valid(fd)) {
      return -1;
   }
   fclose(fds[fd].stream);
   fds[fd].stream = NULL;
   if (fds[fd].rpipe) {
      fds[fd].rpipe->nlink--;
      if (fds[fd].rpipe->nlink == 0) {
         free(fds[fd].rpipe);
      }
   }
   if (fds[fd].wpipe) {
      fds[fd].wpipe->nlink--;
      if (fds[fd].wpipe->nlink == 0) {
         free(fds[fd].wpipe);
      }
   }
   return 0;
}
