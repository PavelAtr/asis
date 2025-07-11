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

ssize_t recv(int sockfd, void *buf, size_t len, int flags) {
    INIT_afds
    if (!fd_is_valid(sockfd)) {
        errno = EBADFD;
        return -1;
    }
    asocket* socket = (asocket*)afds[sockfd];

    // SOCK_SEQPACKET: возвращаем ровно один пакет, если он полностью получен
    if (socket->domain == AF_UNIX && socket->socktype == SOCK_SEQPACKET) {
        if (!socket->connected) {
            errno = ENOTCONN;
            return -1;
        }
        if (socket->sbuf->buflen < sizeof(uint32_t)) {
            // Нет даже длины пакета — ждём данных
            switchtask;
            errno = EAGAIN;
            return -1;
        }
        uint32_t pktlen;
        memcpy(&pktlen, socket->sbuf->buf, sizeof(pktlen));
        if (socket->sbuf->buflen < sizeof(pktlen) + pktlen) {
            // Пакет ещё не полностью получен — ждём
            switchtask;
            errno = EAGAIN;
            return -1;
        }
        // Есть полный пакет
        size_t to_copy = pktlen;
        if (to_copy > len)
            to_copy = len; // если буфер меньше пакета — копируем только часть

        memcpy(buf, socket->sbuf->buf + sizeof(pktlen), to_copy);

        // Сдвигаем буфер (удаляем считанный пакет)
        memmove(socket->sbuf->buf, socket->sbuf->buf + sizeof(pktlen) + pktlen, socket->sbuf->buflen - sizeof(pktlen) - pktlen);
        socket->sbuf->buflen -= sizeof(pktlen) + pktlen;

        return to_copy;
    }

    // SOCK_STREAM: обычное поведение (поток байтов)
    if (socket->domain == AF_UNIX || socket->socktype == SOCK_STREAM) {
        if (!socket->connected) {
            errno = ENOTCONN;
            return -1;
        }
        size_t to_copy = len;
        if (to_copy > socket->sbuf->buflen)
            to_copy = socket->sbuf->buflen;
        memcpy(buf, socket->sbuf->buf, to_copy);
        memmove(socket->sbuf->buf, socket->sbuf->buf + to_copy, socket->sbuf->buflen - to_copy);
        socket->sbuf->buflen -= to_copy;
        if (!to_copy)
            switchtask;
        return to_copy;
    }

    errno = EAFNOSUPPORT;
    return -1;
}
