#ifndef _ARPA_INET_H
#define _ARPA_INET_H

#include <stdint.h>
#include <sys/socket.h>

const char *inet_ntop(int af, const void* src, char* dst, socklen_t size);

uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);

#endif
