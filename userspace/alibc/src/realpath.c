#include <string.h>

/* NOT REALIZED */

char *realpath(const char *path,
                      char * resolved_path)
{
    strcpy(resolved_path, path);
    return resolved_path;
}