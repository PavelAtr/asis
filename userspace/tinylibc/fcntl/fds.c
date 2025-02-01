#include <syscall.h>
#include <stdio.h>
#include <fcntl.h>

FILE** fds;
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
