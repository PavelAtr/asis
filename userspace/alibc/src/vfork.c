#include <syscall.h>
#include <sys/types.h>

pid_t vfork(void)
{
   return (pid_t)asyscall(SYS_FORK, 0, 0, 0, 0, 0, 0);
}