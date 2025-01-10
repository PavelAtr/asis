#include <syscall.h>
#include <unistd.h>

pid_t getpid(void)
{
   return syscall(SYS_GETPID);
}

pid_t getppid(void)
{
   return syscall(SYS_GETPPID);
}

