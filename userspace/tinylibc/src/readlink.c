#include <sys/types.h>
#include <string.h>

/* NOT REALIZED */

ssize_t readlink(const char*pathname, char* buf, size_t bufsiz)
{
    strncpy(buf, pathname, bufsiz);
    return strnlen(buf, bufsiz);
}
