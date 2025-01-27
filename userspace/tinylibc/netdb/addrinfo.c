#include <netdb.h>

/* NOT REALIZED */

int getaddrinfo(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res)
{
   return 0;
}

void freeaddrinfo(struct addrinfo *res)
{
   return;
}

const char *gai_strerror(int errcode)
{
   return "gai_strerror() not realized";
}
