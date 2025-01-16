#include <unistd.h>
#include <string.h>

/* NOT REALIZED */

int gethostname(char *name, size_t len)
{
   const char* hostname = "dummyhostname";
   strncpy(name, hostname, strnlen(hostname, len));
   return 0;
}