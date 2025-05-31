#include <sys/types.h>
#include <syscall.h>


pid_t waitpid(pid_t pid, int* wstatus, int options)
{
   return asyscall(SYS_WAITPID, pid, wstatus, options, 0, 0, 0);
}

pid_t wait(int* wstatus)
{
   return waitpid(-1, wstatus, 0);
}