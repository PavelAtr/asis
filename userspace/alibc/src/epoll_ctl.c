#include <sys/epoll.h>

int epoll_ctl(int epfd, int op, int index, uint32_t events) {
    if (epfd < 0 || epfd >= MAX_EPOLL_OBJECTS || !epoll_objects[epfd].used)
        return -1;
    epoll_object *ep = &epoll_objects[epfd];

    // Поиск существующего target
    int found = -1;
    for (int i = 0; i < ep->num_targets; ++i) {
        if (ep->targets[i].index == index) {
            found = i;
            break;
        }
    }

    if (op == EPOLL_CTL_ADD) {
        if (found != -1) return -1; // Уже есть
        if (ep->num_targets >= MAX_EPOLL_TARGETS) return -1;
        ep->targets[ep->num_targets].index = index;
        ep->targets[ep->num_targets].events = events;
        ep->targets[ep->num_targets].revents = 0;
        ep->num_targets++;
        return 0;
    } else if (op == EPOLL_CTL_DEL) {
        if (found == -1) return -1;
        for (int i = found; i < ep->num_targets - 1; ++i)
            ep->targets[i] = ep->targets[i + 1];
        ep->num_targets--;
        return 0;
    } else if (op == EPOLL_CTL_MOD) {
        if (found == -1) return -1;
        ep->targets[found].events = events;
        return 0;
    }
    return -1;
}
