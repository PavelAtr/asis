#include <syscall.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int execve(const char* path, char* const argv[], char* const envp[])
{
   return asyscall(SYS_EXECVE, path, argv, envp, 0, 0, 0);
}

int execv(const char *pathname, char *const argv[])
{
    return execve(pathname, argv, NULL);
}

int execvp(const char *file, char *const argv[])
{
    return execve(file, argv, NULL);
}
