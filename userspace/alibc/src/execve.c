#include <syscall.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int execve(const char* path, char* const argv[], char* const envp[])
{
   return syscall(SYS_EXECVE, path, argv, envp);
}
