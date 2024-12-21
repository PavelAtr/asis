#ifndef _POLL_H
#define _POLL_H

struct pollfd {
        int fd;
        short events;
        short revents;
};

#endif