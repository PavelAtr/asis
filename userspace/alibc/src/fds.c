#include <syscall.h>
#include <stdio.h>
#include <fcntl.h>

int get_free_fd()
{
   INIT_afds
   int i;
   for (i = 0; i < (int)asyscall(SYS_GETMAXFD, 0, 0, 0, 0, 0, 0); i++)
      if (afds[i] == NULL) {
         return i;
      }
   return -1;
}

char fd_is_valid(int fd) {
   if ((unsigned int)fd < (int)asyscall(SYS_GETMAXFD, 0, 0, 0, 0, 0, 0))
   {
      if (afds[fd]) {
         return 1;
      }
   }
   return 0;
}
