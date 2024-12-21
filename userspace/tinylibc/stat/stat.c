#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int stat(const char* path, struct stat* statbuf)
{
   return syscall(SYS_FSTAT, fullpath(cwd, path), statbuf);
}

int lstat(const char* pathname, struct stat* statbuf)
{
   return stat(fullpath(cwd, pathname), statbuf);
}

