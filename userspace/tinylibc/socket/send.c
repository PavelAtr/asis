#include <sys/types.h>
#include <sys/socket.h>

/* NOT REALIZED */

ssize_t send(int sockfd, const void* buf, size_t len, int flags)
{
   return 0;
}

ssize_t sendto(int sockfd, const void* buf, size_t len, int flags,
                  const struct sockaddr *dest_addr, socklen_t addrlen)
{
   return 0;
}

ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags)
{
   return 0;
}
