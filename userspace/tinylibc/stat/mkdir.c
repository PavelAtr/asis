#include <syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int mkdir(const char* pathname, mode_t mode)
{
   return syscall(SYS_MKNOD, fullpath(get_current_dir_name(), pathname), S_IFDIR |  mode & ~global_mask);
}