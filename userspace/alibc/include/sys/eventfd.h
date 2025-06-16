#ifndef _SYS_EVENTFD_H
#define _SYS_EVENTFD_H

#define EFD_SEMAPHORE 0x1
#define EFD_CLOEXEC 0x2
#define EFD_NONBLOCK 0x04

int eventfd(unsigned int initval, int flags);

#endif