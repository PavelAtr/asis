#include <sys/socket.h>

/* NOT REALIZED */

int socket(int domain, int type, int protocol)
{
   return 0;
}

extern struct cmsghdr *__cmsg_nxthdr (struct msghdr *__mhdr,
                                      struct cmsghdr *__cmsg)
{
  return __cmsg;
}
