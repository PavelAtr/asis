/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <dirent.h>
#include <stdlib.h>
#include <errno.h>

int closedir(DIR *dirp)
{
   if (!dirp) {
      errno = ENOENT;
      return -1;
   }
   if (dirp->fd != -1)
      return 0;
   freefile((FILE*)dirp);
   return 0;
}