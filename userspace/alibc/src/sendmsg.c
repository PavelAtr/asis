/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <sys/uio.h>
#include <string.h>
#include <errno.h>

// Простая реализация sendmsg через send и writev
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags) {
    // Игнорируем msg_name, msg_control для простоты
    ssize_t total = 0;
    for (size_t i = 0; i < msg->msg_iovlen; ++i) {
        ssize_t n = send(sockfd, msg->msg_iov[i].iov_base, msg->msg_iov[i].iov_len, flags);
        if (n < 0) {
            return (total > 0) ? total : -1;
        }
        total += n;
        if ((size_t)n < msg->msg_iov[i].iov_len) {
            // Частичная отправка
            break;
        }
    }
    return total;
}
