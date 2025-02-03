#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int stat(const char* path, struct stat* statbuf)
{
   int a = fds1;
   int b = fds2;
   return syscall(SYS_FSTAT, fullpath(get_current_dir_name(), path), statbuf);
}

int lstat(const char* pathname, struct stat* statbuf)
{
   return stat(fullpath(get_current_dir_name(), pathname), statbuf);
}

int stat64(const char* path, struct stat* statbuf)
{
   return stat(path, statbuf);
}

