/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/uio.h>

int socketpair(int domain, int type, int protocol, int sv[2]) {
    if (domain == AF_UNIX && (type == SOCK_STREAM || type == SOCK_SEQPACKET)) {
      int fd1 = get_free_fd();
      if (fd1 == -1) {
        errno = ENOMEM;
        return -1;
      }
      int fd2 = get_free_fd();
      if (fd2 == -1) {
        errno = ENOMEM;
        return -1;
      }
      afds[fd1] = calloc(1, sizeof(asocket));
      afds[fd1]->type = F_SOCKET;
      initfile(afds[fd1]);
      afds[fd2] = calloc(1, sizeof(asocket));
      afds[fd2]->type = F_SOCKET;
      asocket* socket1 = (asocket*)afds[fd1];
      initfile(afds[fd1]);
      asocket* socket2 = (asocket*)afds[fd2];
      initfile(afds[fd2]);
      socket1->domain = domain;
      socket1->socktype = type;
      socket1->protocol = protocol;
      socket2->domain = domain;
      socket2->socktype = type;
      socket2->protocol = protocol;
      socket1->peer = socket2;
      socket2->peer = socket1;
      sv[0] = fd1;
      sv[1] = fd2;
      return 0;
    }
    errno = EAFNOSUPPORT;
    return -1;
}
