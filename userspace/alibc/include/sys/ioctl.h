#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

int ioctl(int fd, unsigned long request, void* arg1, void* arg2, void* arg3, void* arg4);

#define TIOCGWINSZ   1
#define TIOCNOTTY    2
#define TIOCSWINSZ   3
#define FICLONE	     4


#endif
