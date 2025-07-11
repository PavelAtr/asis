/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags) {
    if (!fd_is_valid(sockfd)) {
        errno = EBADFD;
        return -1;
    }
    asocket* socket = (asocket*)afds[sockfd];

    // SOCK_SEQPACKET: отправляем ровно один пакет с длиной
    if (socket->domain == AF_UNIX && socket->socktype == SOCK_SEQPACKET) {
        if (!socket->connected) {
            errno = ENOTCONN;
            return -1;
        }
        asocket* peer = socket->peer;
        size_t max_payload = sizeof(peer->sbuf->buf) - peer->sbuf->buflen - sizeof(uint32_t);
        size_t to_copy = len;
        if (to_copy > max_payload)
            to_copy = max_payload;
        if (to_copy == 0) {
            switchtask;
            errno = EAGAIN;
            return -1;
        }
        uint32_t pktlen = (uint32_t)to_copy;
        memcpy(peer->sbuf->buf + peer->sbuf->buflen, &pktlen, sizeof(pktlen));
        peer->sbuf->buflen += sizeof(pktlen);
        memcpy(peer->sbuf->buf + peer->sbuf->buflen, buf, to_copy);
        peer->sbuf->buflen += to_copy;
        return to_copy;
    }

    // SOCK_STREAM: обычное поведение (поток байтов)
    if (socket->domain == AF_UNIX || socket->socktype == SOCK_STREAM) {
        if (!socket->connected) {
            errno = ENOTCONN;
            return -1;
        }
        asocket* peer = socket->peer;
        size_t to_copy = len;
        if (to_copy > sizeof(peer->sbuf->buf) - peer->sbuf->buflen)
            to_copy = sizeof(peer->sbuf->buf) - peer->sbuf->buflen;
        if (to_copy == 0) {
            switchtask;
            errno = EAGAIN;
            return -1;
        }
        memcpy(peer->sbuf->buf + peer->sbuf->buflen, buf, to_copy);
        peer->sbuf->buflen += to_copy;
        return to_copy;
    }

    errno = EAFNOSUPPORT;
    return -1;
}
