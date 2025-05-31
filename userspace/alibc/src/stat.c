#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int stat(const char* path, struct stat* statbuf)
{
   return asyscall(SYS_FSTAT, fullpath(get_current_dir_name(), path), statbuf, 0, 0, 0, 0);
}

int lstat(const char* pathname, struct stat* statbuf)
{
   return stat(fullpath(get_current_dir_name(), pathname), statbuf);
}
