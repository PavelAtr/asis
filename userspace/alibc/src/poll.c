#include <sys/poll.h>
#include <sys/epoll.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

int poll(struct pollfd *fds, unsigned long nfds, int timeout) {
    struct epoll_event events[MAX_EPOLL_EVENTS];
    int epfd = epoll_create(1);
    if (epfd < 0) return -1;

    // Добавляем все fd в epoll
    for (unsigned long i = 0; i < nfds; ++i) {
        struct epoll_event ev = {0};
        ev.events = fds[i].events;
        ev.data.fd = fds[i].fd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, fds[i].fd, &ev);
    }

    int n = epoll_wait(epfd, events, MAX_EPOLL_EVENTS, timeout);

    // Обнуляем revents
    for (unsigned long i = 0; i < nfds; ++i)
        fds[i].revents = 0;

    // Заполняем revents для каждого pollfd
    for (int i = 0; i < n; ++i) {
        for (unsigned long j = 0; j < nfds; ++j) {
            if (fds[j].fd == events[i].data.fd)
                fds[j].revents |= events[i].events;
        }
    }

    // epoll_create1 не нужен, epoll_close не реализован — просто возвращаем результат
    return n;
}

int ppoll(struct pollfd *fds, unsigned long nfds,
          const struct timespec *timeout, const sigset_t *sigmask) {
    int ms = -1;
    if (timeout)
        ms = timeout->tv_sec * 1000 + timeout->tv_nsec / 1000000;
    // (sigmask игнорируется в этой реализации)
    return poll(fds, nfds, ms);
}
