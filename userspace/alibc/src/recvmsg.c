/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <sys/uio.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <alloca.h>

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {
    asocket* socket = (asocket*)afds[sockfd];
    if (socket && socket->domain == AF_UNIX && socket->socktype == SOCK_SEQPACKET) {
        // Получаем ровно один пакет в temp-буфер
        char tempbuf[MAX_PACKET_SIZE];
        ssize_t n = recv(sockfd, tempbuf, sizeof(tempbuf), flags);
        if (n <= 0) return n;
        // Раскладываем по iovec
        size_t left = n, pos = 0, copied = 0;
        for (size_t i = 0; i < msg->msg_iovlen && left > 0; ++i) {
            size_t to_copy = msg->msg_iov[i].iov_len;
            if (to_copy > left) to_copy = left;
            memcpy(msg->msg_iov[i].iov_base, tempbuf + pos, to_copy);
            pos += to_copy;
            left -= to_copy;
            copied += to_copy;
        }
        return copied;
    }
    // Для остальных — как раньше
    ssize_t total = 0;
    for (size_t i = 0; i < msg->msg_iovlen; ++i) {
        ssize_t n = recv(sockfd, msg->msg_iov[i].iov_base, msg->msg_iov[i].iov_len, flags);
        if (n < 0) return (total > 0) ? total : -1;
        total += n;
        if ((size_t)n < msg->msg_iov[i].iov_len) break;
    }
    return total;
}


