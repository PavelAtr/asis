#include <fcntl.h>
#include <sys/stat.h>

int creat(const char *pathname, mode_t mode)
{
   return open(pathname, O_CREAT, S_IFREG | 0666 & ~mask);
}
