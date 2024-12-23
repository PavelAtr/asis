#ifndef _POLL_H
#define _POLL_H

struct pollfd {
        int fd;
        short events;
        short revents;
};

/* Type used for the number of file descriptors.  */
typedef unsigned long int nfds_t;

int poll(struct pollfd *fds, nfds_t nfds, int timeout);

/* These are specified by iBCS2 */
#define POLLIN          0x0001
#define POLLPRI         0x0002
#define POLLOUT         0x0004
#define POLLERR         0x0008
#define POLLHUP         0x0010
#define POLLNVAL        0x0020


#endif