#include <syscall.h>
#include <unistd.h>

pid_t getpid(void)
{
   return (pid_t)asyscall(SYS_GETPID, 0, 0, 0, 0, 0, 0);
}

pid_t getppid(void)
{
   return (pid_t)asyscall(SYS_GETPPID, 0, 0, 0, 0, 0, 0);
}

