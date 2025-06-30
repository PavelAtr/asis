/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>

ssize_t writev(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t total = 0;
    for (int i = 0; i < iovcnt; ++i) {
        ssize_t n = write(fd, iov[i].iov_base, iov[i].iov_len);
        if (n < 0) {
            return (total > 0) ? total : -1;
        }
        total += n;
        if (n < (ssize_t)iov[i].iov_len) {
            // Partial write
            break;
        }
    }
    return total;
}