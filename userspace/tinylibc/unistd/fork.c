#include <unistd.h>

pid_t fork(void)
{
  return vfork();
}
