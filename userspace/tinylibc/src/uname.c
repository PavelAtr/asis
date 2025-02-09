#include <sys/utsname.h>

int uname(struct utsname *buf)
{
   buf->sysname = "TinySys";
   buf->nodename = "localhost";
   buf->release = "0.0001b";
   buf->version = "0.0001b";
   buf->machine = "x86_64";
   #ifdef _GNU_SOURCE
      buf->domainname = "localdomain"; /* NIS or YP domain name */
   #endif
}
