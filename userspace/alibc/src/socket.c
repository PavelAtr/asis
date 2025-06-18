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


int socket(int domain, int type, int protocol) {
    if (domain == AF_UNIX && type == SOCK_STREAM) {
      int fd = get_free_fd();
      if (fd == -1) {
        errno = ENOMEM;
        return -1;
      }
      afds[fd] = calloc(1, sizeof(asocket));
      afds[fd]->type = F_SOCKET;
      asocket* socket = (asocket*)afds[fd];
      initfile(afds[fd]);
      socket->domain = domain;
      socket->socktype = type;
      socket->protocol = protocol;
      return fd;
    }
    errno = EAFNOSUPPORT;
    return -1;
}

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    INIT_afds
    if (!fd_is_valid(sockfd)) {
      errno = EBADFD;
      return -1;
    }
    asocket* socket = (asocket*)afds[sockfd];
    if (socket->domain == AF_UNIX || socket->socktype == SOCK_STREAM) {
      const struct sockaddr_un *un = (const struct sockaddr_un *)addr;
      strncpy(socket->path, un->sun_path, sizeof(socket->path) - 1);
      socket->bound = 1;
      return 0;
    }
    errno = EAFNOSUPPORT;
    return -1;
  }

/*
extern struct cmsghdr *__cmsg_nxthdr (struct msghdr *__mhdr,
                                      struct cmsghdr *__cmsg)
{
  return __cmsg;
}
*/