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


int getsockname(int sockfd, struct sockaddr * addr,
                       socklen_t *restrict addrlen)
{
    INIT_afds
    if (!fd_is_valid(sockfd)) {
      errno = EBADFD;
      return -1;
    }
    asocket* socket = (asocket*)afds[sockfd];
    if (socket->domain == AF_UNIX || socket->socktype == SOCK_STREAM) {
      const struct sockaddr_un *un = (const struct sockaddr_un *)addr;
      strncpy(socket->path, un->sun_path, sizeof(socket->path) - 1);
      return 0;
    }
    errno = EAFNOSUPPORT;
    return -1;
}

