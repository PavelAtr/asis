#ifndef _SYS_UIO_H
#define _SYS_UIO_H

#include <sys/types.h>

       struct iovec {
           void   *iov_base;  /* Starting address */
           size_t  iov_len;   /* Size of the memory pointed to by iov_base. */
       };

#endif