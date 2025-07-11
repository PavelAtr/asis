/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <sys/uio.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <alloca.h>


ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags) {
    asocket* socket = (asocket*)afds[sockfd];
    if (socket && socket->domain == AF_UNIX && socket->socktype == SOCK_SEQPACKET) {
        // Считаем общий размер
        size_t total = 0;
        for (size_t i = 0; i < msg->msg_iovlen; ++i)
            total += msg->msg_iov[i].iov_len;
        char *buf = alloca(total);
        size_t pos = 0;
        for (size_t i = 0; i < msg->msg_iovlen; ++i) {
            memcpy(buf + pos, msg->msg_iov[i].iov_base, msg->msg_iov[i].iov_len);
            pos += msg->msg_iov[i].iov_len;
        }
        return send(sockfd, buf, total, flags);
    }
    // Для остальных — как раньше
    ssize_t total = 0;
    for (size_t i = 0; i < msg->msg_iovlen; ++i) {
        ssize_t n = send(sockfd, msg->msg_iov[i].iov_base, msg->msg_iov[i].iov_len, flags);
        if (n < 0) return (total > 0) ? total : -1;
        total += n;
        if ((size_t)n < msg->msg_iov[i].iov_len) break;
    }
    return total;
}

