#include <sys/epoll.h>

epoll_object epoll_objects[MAX_EPOLL_OBJECTS];

int epoll_create(int size) {
    for (int i = 0; i < MAX_EPOLL_OBJECTS; ++i) {
        if (!epoll_objects[i].used) {
            epoll_objects[i].used = 1;
            epoll_objects[i].num_targets = 0;
            epoll_objects[i].num_ready = 0;
            return i; // возвращаем индекс как epoll "fd"
        }
    }
    return -1;
}
