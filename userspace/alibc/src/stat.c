#include <syscall.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int stat(const char* path, struct stat* statbuf)
{
   errno = (int)asyscall(SYS_FSTAT, path, statbuf, 0, 0, 0, 0);
   if (errno) {
	   return -1;
   }
   return 0;
}

int lstat(const char* pathname, struct stat* statbuf)
{
   return stat(pathname, statbuf);
}
