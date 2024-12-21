#include <syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int mknod(const char *pathname, mode_t mode, dev_t dev)
{
   return syscall(SYS_MKNOD, fullpath(cwd, pathname), mode & ~global_mask);
}
