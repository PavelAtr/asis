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

ssize_t recv(int sockfd, void *buf, size_t len, int flags) {
   INIT_afds
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
      if (to_copy > socket->buflen)
           to_copy = socket->buflen;
      memcpy(buf, socket->buf, to_copy);
      memmove(socket->buf, socket->buf + to_copy, socket->buflen - to_copy);
      socket->buflen -= to_copy;
      if (!to_copy)
         switchtask;
      return to_copy;
   }
   errno = EAFNOSUPPORT;
   return 0;   
}