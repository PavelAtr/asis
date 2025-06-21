/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
   if (!fd_is_valid(sockfd)) {
      errno = EBADFD;
      return -1;
   }
   asocket* socket = (asocket*)afds[sockfd];
   if (socket->domain == AF_UNIX || socket->socktype == SOCK_STREAM) {
      if (!socket->connected) {
           errno = ENOTCONN;
         return -1;
      }
      size_t to_copy = len;
      asocket* peer = socket->peer;
      if (to_copy > sizeof(peer->buf) - peer->buflen)
         to_copy = sizeof(peer->buf) - peer->buflen;
      memcpy(peer->buf + peer->buflen, buf, to_copy);
      peer->buflen += to_copy;
      if (!to_copy)
         switchtask;
      return to_copy;
   }
   errno = EAFNOSUPPORT;
   return 0;    
}

