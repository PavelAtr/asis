#ifndef _NETDB_H
#define _NETDB_H

#include <sys/socket.h>

struct addrinfo
{
  int ai_flags;                 /* Input flags.  */
  int ai_family;                /* Protocol family for socket.  */
  int ai_socktype;              /* Socket type.  */
  int ai_protocol;              /* Protocol for socket.  */
  socklen_t ai_addrlen;         /* Length of socket address.  */
  struct sockaddr *ai_addr;     /* Socket address for socket.  */
  char *ai_canonname;           /* Canonical name for service location.  */
  struct addrinfo *ai_next;     /* Pointer to next in list.  */
};

/* Possible values for `ai_flags' field in `addrinfo' structure.  */
# define AI_PASSIVE     0x0001  /* Socket address is intended for `bind'.  */
# define AI_CANONNAME   0x0002  /* Request for canonical name.  */
# define AI_NUMERICHOST 0x0004  /* Don't use name resolution.  */
# define AI_V4MAPPED    0x0008  /* IPv4 mapped addresses are acceptable.  */
# define AI_ALL         0x0010  /* Return IPv4 mapped and IPv6 addresses.  */
# define AI_ADDRCONFIG  0x0020  /* Use configuration of this host to choose
                                   returned address type..  */

int getaddrinfo(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res);
void freeaddrinfo(struct addrinfo *res);
const char *gai_strerror(int errcode);

#endif