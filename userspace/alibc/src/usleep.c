#include <unistd.h>
#include <syscall.h>

int usleep(unsigned long usec)
{
   return (int)asyscall(SYS_USLEEP, usec, 0, 0, 0, 0, 0);
}
