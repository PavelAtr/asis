/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <dirent.h>
#include <syscall.h>

struct dirent* readdir(DIR *dirp)
{
   struct dirent* dent = (struct dirent*)asyscall(SYS_READDIR, dirp->file,  dirp->ndx, 0, 0, 0, 0);
   dirp->ndx++;
   return dent;
}
