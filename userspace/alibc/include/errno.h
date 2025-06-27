#ifndef _ERRNO_H
#define _ERRNO_H

#define program_invocation_name (*core_argv[0])
#define program_invocation_short_name basename(*core_argv[0])

extern __thread int errno;

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
#define EWOULDBLOCK 20
#define ENODATA 26
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
#define ETXTBSY 38
#define EMLINK 39
#define EDQUOT 40
#define EROFS 41
#define ENOTEMPTY 42
#define ECHILD 43
#define ENFILE 44
#define ENOTTY 45
#define EDEADLK 46
#define EINPROGRESS 47
#define ECONNRESET 48
#define ESHUTDOWN 49
#define EFAULT 50
#define EPROTO 51
#define ECONNREFUSED 52
#define ENOTCONN 53
#define ENODEV 54
#define ENXIO 55
#define ENOTSOCK 56
#define EBADMSG 57

#endif
