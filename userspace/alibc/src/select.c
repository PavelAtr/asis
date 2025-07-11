
#include <sys/select.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <signal.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout) {
    struct epoll_event events[MAX_EPOLL_EVENTS];
    int epfd = epoll_create(1);
    if (epfd < 0) return -1;

    // Добавляем все fd из readfds/writefds/exceptfds
    for (int fd = 0; fd < nfds; ++fd) {
        uint32_t ev = 0;
        if (readfds && FD_ISSET(fd, readfds)) ev |= EPOLLIN;
        if (writefds && FD_ISSET(fd, writefds)) ev |= EPOLLOUT;
        if (exceptfds && FD_ISSET(fd, exceptfds)) ev |= EPOLLPRI;
        if (ev) {
            struct epoll_event epev = {0};
            epev.events = ev;
            epev.data.fd = fd;
            epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &epev);
        }
    }

    int ms = -1;
    if (timeout)
        ms = timeout->tv_sec * 1000 + timeout->tv_usec / 1000;

    int n = epoll_wait(epfd, events, MAX_EPOLL_EVENTS, ms);

    // Обнуляем все fd_set
    if (readfds) FD_ZERO(readfds);
    if (writefds) FD_ZERO(writefds);
    if (exceptfds) FD_ZERO(exceptfds);

    // Заполняем fd_set по событиям
    for (int i = 0; i < n; ++i) {
        int fd = events[i].data.fd;
        if (readfds && (events[i].events & EPOLLIN)) FD_SET(fd, readfds);
        if (writefds && (events[i].events & EPOLLOUT)) FD_SET(fd, writefds);
        if (exceptfds && (events[i].events & EPOLLPRI)) FD_SET(fd, exceptfds);
    }

    return n;
}

int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
            const struct timespec *timeout, const sigset_t *sigmask) {
    struct timeval tv, *ptv = NULL;
    if (timeout) {
        tv.tv_sec = timeout->tv_sec;
        tv.tv_usec = timeout->tv_nsec / 1000;
        ptv = &tv;
    }
    // (sigmask игнорируется в этой реализации)
    return select(nfds, readfds, writefds, exceptfds, ptv);
}
