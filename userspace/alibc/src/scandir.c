#include <dirent.h>


/* NOT REALIZED */

int scandir(const char * dirp,
           struct dirent *** namelist,
           int (*filter)(const struct dirent *),
           int (*compar)(const struct dirent **,
                         const struct dirent **))
{
    return 0;
}
