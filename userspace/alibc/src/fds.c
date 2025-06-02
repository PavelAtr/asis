#include <syscall.h>
#include <stdio.h>
#include <fcntl.h>

int get_free_fd()
{
   INIT_FDS
   int i;
   for (i = 0; i < (int)asyscall(SYS_GETMAXFD, 0, 0, 0, 0, 0, 0); i++)
      if (fds[i] == NULL) {
         return i;
      }
   return -1;
}

char fd_is_valid(int fd) {
   if ((unsigned int)fd < (int)asyscall(SYS_GETMAXFD, 0, 0, 0, 0, 0, 0))
   {
      if (fds[fd]) {
         return 1;
      }
   }
   return 0;
}
