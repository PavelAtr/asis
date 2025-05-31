#include <unistd.h>
#include <syscall.h>
#include <tiny.h>
#include <stdlib.h>

int truncate(const char *path, off_t length)
{
   return asyscall(SYS_TRUNCATE, path, length, 0, 0, 0, 0);
}