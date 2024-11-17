#include <unistd.h>
#include <syscall.h>
#include <tiny.h>
#include <stdlib.h>

int truncate(const char *path, off_t length)
{
    return syscall(SYS_TRUNCATE, path, length);
}