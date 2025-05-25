#ifndef _ARPA_INET_H
#define _ARPA_INET_H

#include <sys/socket.h>

const char *inet_ntop(int af, const void* src, char* dst, socklen_t size);

#endif