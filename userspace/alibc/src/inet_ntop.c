#include <arpa/inet.h>
#include <string.h>

/* NOT REALIZED*/

const char *inet_ntop(int af, const void* src, char* dst, socklen_t size)
{
   strncpy(dst, "BAD INET ADDR", size);
   return dst;
}