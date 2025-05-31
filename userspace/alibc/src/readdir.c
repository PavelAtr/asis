#include <dirent.h>
#include <syscall.h>

struct dirent* readdir(DIR *dirp)
{
   struct dirent* dent = (struct dirent*)asyscall(SYS_READDIR, dirp->dir,  dirp->ndx, 0, 0, 0, 0);
   dirp->ndx++;
   return dent;
}
