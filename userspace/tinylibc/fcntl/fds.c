#include <syscall.h>
#include <fcntl.h>

int get_free_fd()
{
  int i;
  for (i = 0; i < MAXFD; i++)
    if (fds[i].stream == NULL)
      return i;
  return -1;
}
