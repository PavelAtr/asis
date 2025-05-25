#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

int ioctl(int fd, unsigned long request, ...);

#define TIOCGWINSZ   1
#define TIOCNOTTY    2
#define TIOCSWINSZ   3
#define FICLONE	     4


#endif
