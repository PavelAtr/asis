#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>

#define is_pipe(idx) (afds[idx]->type == F_PIPE || afds[idx]->type == F_NAMEDMEM)
#define pipe_has_data(idx) (((apipe*)afds[idx])->pbuf->writepos > ((apipe*)afds[idx])->pbuf->readpos)
#define pipe_can_write(idx) (((apipe*)afds[idx])->pbuf->writepos < MAXPIPE || afds[idx]->type & F_NAMEDMEM)

#define is_socket(idx) (afds[idx]->type == F_SOCKET)
#define socket_has_data(idx) (((asocket*)afds[idx])->buflen > 0)
#define socket_can_write(idx) (((asocket*)afds[idx])->buflen < sizeof(((asocket*)afds[idx])->buf))



uint32_t check_events(int idx, uint32_t req_events) {
    // Пример для pipebuf:
    if (is_pipe(idx)) {
        uint32_t ev = 0;
        if (pipe_has_data(idx)) ev |= EPOLLIN;
        if (pipe_can_write(idx)) ev |= EPOLLOUT;
        return ev & req_events;
    }
    if (is_socket(idx)) {
        uint32_t ev = 0;
        if (socket_has_data(idx)) ev |= EPOLLIN;
        if (socket_can_write(idx)) ev |= EPOLLOUT;
        return ev & req_events;
    }
    // Для других типов аналогично
    return 0;
}

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout) {
    if (epfd < 0 || epfd >= MAX_EPOLL_OBJECTS || !epoll_objects[epfd].used)
        return -1;
    epoll_object *ep = &epoll_objects[epfd];
    int n = 0;

    int waited = 0;
    int interval = 10; // миллисекунд между проверками

    do {
        n = 0;
        ep->num_ready = 0;

        for (int i = 0; i < ep->num_targets && n < maxevents; ++i) {
            int idx = ep->targets[i].index;
            uint32_t req_events = ep->targets[i].events;
            uint32_t got_events = 0;

            got_events = check_events(idx, req_events);

            if (got_events & req_events) {
                events[n].events = got_events & req_events;
                events[n].index = idx;
                n++;
            }
        }

        if (n > 0 || timeout == 0)
            break;

        if (timeout > 0) {
            usleep(interval * 1000);
            waited += interval;
        }
    } while (n == 0 && (timeout < 0 || waited < timeout));

    return n;
}

