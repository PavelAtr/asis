#include <syscall.h>
#include <tiny.h>

int execve(const char* path, char* const argv[], char* const envp[])
{
    return syscall(SYS_EXECVE, path, argv, envp);
}
