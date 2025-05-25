#include <unistd.h>
#include <syscall.h>

unsigned int sleep(unsigned int seconds)
{
   return syscall(SYS_USLEEP, (unsigned long)(1000000 * seconds));
}
