/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <syscall.h>

int listen(int sockfd, int backlog) {
    INIT_afds
    if (!fd_is_valid(sockfd)) {
        errno = EBADFD;
        return -1;
    }
    asocket* socket = (asocket*)afds[sockfd];
    if (socket->domain == AF_UNIX && socket->socktype == SOCK_STREAM) {
        if (!asyscall(SYS_LISTEN, socket, 0, 0, 0, 0, 0)) {
            socket->listening = 1;
            socket->backlog = (backlog > UNIX_LISTEN_BACKLOG) ? UNIX_LISTEN_BACKLOG : backlog;
            socket->num_pending = 0;
            return 0;
        }
        errno = ECONNREFUSED;
        return -1;
    }
    errno = EAFNOSUPPORT;
    return -1;
}