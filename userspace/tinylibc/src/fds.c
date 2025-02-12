#include <syscall.h>
#include <stdio.h>
#include <fcntl.h>

int get_free_fd()
{
   INIT_FDS
   int i;
   for (i = 0; i < syscall(SYS_GETMAXFD); i++)
      if (fds[i] == NULL) {
         return i;
      }
   return -1;
}

char fd_is_valid(int fd) {
   if ((unsigned int)fd < syscall(SYS_GETMAXFD))
   {
      if (fds[fd]) {
         return 1;
      }
   }
   return 0;
}
