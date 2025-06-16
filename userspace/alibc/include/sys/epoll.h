#ifndef _SYS_EPOLL_H
#define _SYS_EPOLL_H

#include <sys/types.h>
#include <stdint.h>

#define MAX_EPOLL_OBJECTS 128
#define MAX_EPOLL_EVENTS  64
#define MAX_EPOLL_TARGETS 64

#define EPOLLIN      0x001   // Данные доступны для чтения
#define EPOLLPRI     0x002   // Приоритетные данные для чтения
#define EPOLLOUT     0x004   // Можно записывать данные
#define EPOLLERR     0x008   // Ошибка
#define EPOLLHUP     0x010   // Разрыв соединения (hang up)
#define EPOLLRDNORM  0x040   // Обычные данные для чтения
#define EPOLLRDBAND  0x080   // Приоритетные данные для чтения
#define EPOLLWRNORM  0x100   // Обычные данные для записи
#define EPOLLWRBAND  0x200   // Приоритетные данные для записи
#define EPOLLMSG     0x400   // Зарезервировано
#define EPOLLRDHUP   0x2000  // Закрытие чтения peer'ом

typedef union epoll_data {
    void        *ptr;
    int          fd;
    uint32_t     u32;
    uint64_t     u64;
} epoll_data_t;

struct epoll_event {
    uint32_t events; // EPOLLIN, EPOLLOUT и т.д.
    epoll_data_t data; // пользовательские данные
    int index;         // (можно оставить для совместимости с вашей системой)
};

typedef struct {
    int used;
    struct epoll_target {
        int index;      // индекс отслеживаемого объекта (например, pipe, memfd и т.д.)
        uint32_t events; // EPOLLIN, EPOLLOUT и т.д.
        uint32_t revents; // события, которые реально произошли
    } targets[MAX_EPOLL_TARGETS];
    int num_targets;
    struct epoll_event ready[MAX_EPOLL_EVENTS];
    int num_ready;
} epoll_object;

extern epoll_object epoll_objects[MAX_EPOLL_OBJECTS];

#define EPOLL_CTL_ADD 1
#define EPOLL_CTL_DEL 2
#define EPOLL_CTL_MOD 3

int epoll_create(int size);
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
int epoll_ctl(int epfd, int op, int index, struct epoll_event* event);


#endif