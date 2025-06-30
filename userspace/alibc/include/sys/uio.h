#ifndef _SYS_UIO_H
#define _SYS_UIO_H

#include <sys/types.h>

       struct iovec {
           void   *iov_base;  /* Starting address */
           size_t  iov_len;   /* Size of the memory pointed to by iov_base. */
       };

ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#endif

