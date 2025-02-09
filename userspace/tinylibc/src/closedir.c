#include <dirent.h>
#include <stdlib.h>
#include <errno.h>

int closedir(DIR *dirp)
{
   if (!dirp) {
      errno = ENOENT;
      return -1;
   }
   free(dirp);
   return 0;
}