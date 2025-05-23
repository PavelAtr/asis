#ifndef _ERRNO_H
#define _ERRNO_H

#include <sys/types.h>

extern int errno;

#define ESUCCESS 0
#define EPERM 1
#define EACCES 2
#define ENOENT 3
#define ENOMEM 4
#define EEXIST 5
#define ENOTDIR 6
#define ENOTSUP 7
#define EISDIR 8
#define ESPIPE 9
#define ERANGE 10
#define EBADFD 11
#define ENOSPC 12
#define EINVAL 13
#define ENOSYS 14
#define EFTYPE 15
#define ENAMETOOLONG 16
#define EFBIG 17
#define EPIPE 18
#define EINTR 19
#define EAGAIN 20
#define ELOOP 21
#define ESRCH 22
#define E2BIG 23
#define EMFILE 24
#define ENOEXEC 25
#define EWOULDBLOCK 26
#define EBADF 27
#define EBADR 28
#define EOPNOTSUPP 29
#define EBUSY 30
#define EAFNOSUPPORT 31
#define EIO 32
#define EOVERFLOW 33
#define EXDEV 34
#define EILSEQ 35
#define ETIMEDOUT 36
#define ESTALE 37

#endif
