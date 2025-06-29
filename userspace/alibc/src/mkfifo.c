#include <syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int mkfifo(const char *pathname, mode_t mode)
{
    return (int)asyscall(SYS_MKNOD, pathname, S_IFIFO | mode & mask(), 0, 0, 0, 0);
}