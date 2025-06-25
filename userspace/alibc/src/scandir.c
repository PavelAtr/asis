#include <dirent.h>


/* NOT REALIZED STUB USED */

int scandir(const char * dirp,
           struct dirent *** namelist,
           int (*filter)(const struct dirent *),
           int (*compar)(const struct dirent **,
                         const struct dirent **))
{
    return 0;
}

int alphasort(const struct dirent **a, const struct dirent **b)
{
    return 0;
}

int versionsort(const struct dirent **a, const struct dirent **b)
{
    return 0;
}