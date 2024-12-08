#include <unistd.h>
#include <syscall.h>

int usleep(unsigned long usec)
{
   return syscall(SYS_USLEEP, usec);
}
