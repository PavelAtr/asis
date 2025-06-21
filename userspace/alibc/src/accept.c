/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    INIT_afds
    if (!fd_is_valid(sockfd)) {
      errno = EBADFD;
      return -1;
    }
    asocket* socket = (asocket*)afds[sockfd];
    if (socket->domain == AF_UNIX && socket->socktype == SOCK_STREAM) {
        if (!socket->listening) {
            errno = EINVAL;
            return -1;
        }
        if (socket->num_pending == 0) {
            errno = EAGAIN;
            return -1;
        }
        int fd = get_free_fd();
        if (fd == -1) {
            errno = ENOMEM;
            return -1;
        }
        asocket* newsocket = (asocket*)afds[fd];
        asocket* peer = socket->pending[0];
        // Сдвинуть очередь pending
        for (int i = 1; i < socket->num_pending; ++i)
            socket->pending[i-1] = socket->pending[i];
        socket->num_pending--;

        // Установить соединение
        newsocket = calloc(1, sizeof(asocket));
        newsocket->type = F_SOCKET;
        initfile((FILE*)newsocket);
        newsocket->connected = 1;
        newsocket->peer = peer;
        newsocket->bound = 0;
        newsocket->listening = 0;
        newsocket->domain = AF_UNIX;
        newsocket->socktype = SOCK_STREAM;
        
        peer->connected = 1;
        peer->peer = newsocket;
        // Вернуть адрес, если нужно
        if (addr && addrlen) {
            struct sockaddr_un *un = (struct sockaddr_un *)addr;
            un->sun_family = AF_UNIX;
            strncpy(un->sun_path, socket->path, sizeof(un->sun_path)-1);
            *addrlen = sizeof(struct sockaddr_un);
        }
        afds[fd] = (FILE*)newsocket;
        return fd;
    }
    errno = EAFNOSUPPORT;
    return -1;
}
