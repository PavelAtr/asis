#include <syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int mkdir(const char* pathname, mode_t mode)
{
   return syscall(SYS_MKNOD, pathname, S_IFDIR |  mode & ~global_mask);
}