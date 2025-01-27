#include <syscall.h>
#include <fcntl.h>

int get_free_fd()
{
   int i;
   for (i = 0; i < syscall(SYS_GETMAXFD); i++)
      if (fds[i] == NULL) {
         return i;
      }
   return -1;
}
