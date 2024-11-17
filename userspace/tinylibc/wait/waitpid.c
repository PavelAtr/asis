#include <sys/types.h>
#include <syscall.h>


pid_t waitpid(pid_t pid, int* wstatus, int options)
{
    return syscall(SYS_WAITPID, pid, wstatus, options);
}

pid_t wait(int* wstatus)
{
    return waitpid(-1, wstatus, 0);
}