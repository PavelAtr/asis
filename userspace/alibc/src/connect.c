/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <syscall.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
   INIT_afds
   if (!fd_is_valid(sockfd)) {
      errno = EBADFD;
      return -1;
   }
   asocket* socket = (asocket*)afds[sockfd];
   if (socket->domain == AF_UNIX && socket->socktype == SOCK_STREAM) {
      asocket* peer = asyscall(SYS_CONNECT, socket, addr, 0, 0, 0, 0);
      if (peer) {
         socket->connected = 1;
         socket->peer = peer;
         return 0;
      } 
      errno = ECONNREFUSED;
      return -1;
   }
   errno = EAFNOSUPPORT;
   return -1;
}