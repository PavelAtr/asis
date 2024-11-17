#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <errno.h>

ssize_t write(int f, const void* buf, size_t count)
{
    if (!fd_is_valid(f))
    {
    set_errno(BADFD);
    return -1;
    }

    return fwrite(buf, count, 1, fds[f].stream);
}
