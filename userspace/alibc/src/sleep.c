#include <unistd.h>
#include <syscall.h>

unsigned int sleep(unsigned int seconds)
{
   return asyscall(SYS_USLEEP, (unsigned long)(1000000 * seconds), 0, 0, 0, 0, 0);
}
