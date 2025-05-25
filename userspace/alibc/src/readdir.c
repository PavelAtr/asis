#include <dirent.h>
#include <syscall.h>

struct dirent* readdir(DIR *dirp)
{
   struct dirent* dent = (struct dirent*)syscall(SYS_READDIR, dirp->dir,
         dirp->ndx);
   dirp->ndx++;
   return dent;
}
