#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

typedef unsigned int socklen_t;
typedef unsigned short sa_family_t;

struct sockaddr {
  sa_family_t     sa_family;      /* Address family */
  char            sa_data[];      /* Socket address */
};

struct sockaddr_storage {
  sa_family_t     ss_family;      /* Address family */
};

#endif