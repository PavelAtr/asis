#include <sys/types.h>
#include <string.h>

/* NOT REALIZED */

ssize_t readlinkat(int dirfd, const char* pathname, char* buf, size_t bufsiz)
{
    strcpy(buf, pathname);
    return strlen(pathname);
}