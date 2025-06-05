#include <syscall.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int execve(const char* path, char** iargv, char** envp)
{
   return (int)asyscall(SYS_EXECVE, path, iargv, envp, 0, 0, 0);
}

int execv(const char *pathname, char** iargv)
{
    return execve(pathname, iargv, NULL);
}

int execvp(const char *file, char** iargv)
{
    return execve(file, iargv, NULL);
}
