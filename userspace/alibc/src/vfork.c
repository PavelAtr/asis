#include <syscall.h>
#include <sys/types.h>

pid_t vfork(void)
{
   return asyscall(SYS_FORK, 0, 0, 0, 0, 0, 0);
}