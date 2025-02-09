#include <dirent.h>

void rewinddir(DIR *dirp)
{
   dirp->ndx = 0;
}
