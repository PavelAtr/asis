#ifndef _SYS_FILE_H
#define _SYS_FILE_H

#include <sys/file.h>

int flock(int fd, int operation);

#define LOCK_SH 1
#define LOCK_EX 2
#define LOCK_NB 3
#define LOCK_UN 4

#endif