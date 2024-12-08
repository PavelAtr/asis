#include <fcntl.h>

int fcntl(int fd, int cmd, ... /* arg */ )
{
  switch (cmd) {
  case F_GETFL:
    /* notrealized */
    return O_RDWR;
  default:
    break;
  }
  return -1;
}
