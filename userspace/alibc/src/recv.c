#include <sys/socket.h>

/* NOT REALIZED */

ssize_t recv(int sockfd, void* buf, size_t len, int flags)
{
   return 0;
}

ssize_t recvfrom(int sockfd, void* buf, size_t len,
                int flags, struct sockaddr* src_addr,
                socklen_t* addrlen)
{
   return 0;
}

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags)
{
   return 0;
}