#ifndef _SYS_IOCTL_H
#define _SYS_IOCTL_H

#include <asm-generic/ioctl.h>

int aioctl(int fd, unsigned long request, void* arg1, void* arg2, void* arg3, void* arg4);

#define TIOCGWINSZ   1
#define TIOCNOTTY    2
#define TIOCSWINSZ   3
#define FICLONE	     4

#define ioctl(f, r, p) aioctl(f, r, (void*)p, 0, 0, 0)


#endif
