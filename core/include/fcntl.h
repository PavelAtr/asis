#ifndef _FCNTL_H
#define _FCNTL_H

#include <stdio.h>

#define O_CLOEXEC 0x01
#define O_RDONLY 0x02
#define O_RDWR 0x04
#define O_WRONLY 0x08
#define O_CREAT 0x10
#define O_TRUNC 0x20
#define O_APPEND 0x40
#define O_EXCL 0x80
#define O_ACCMODE 0x100

#define MAXPIPE 512

typedef struct {
  char buf[MAXPIPE];
  unsigned short size;
  unsigned short nlink;
  unsigned short writepos;
  unsigned short readpos;
} pipebuf;

typedef struct {
  FILE* stream;
  int flags;
  pipebuf* wpipe;
  pipebuf* rpipe;
} fdesc;

#define MAXFD syscall(SYS_GETMAXFD)
extern fdesc* fds;
int get_free_fd(void);
#define fd_is_valid(fd) ((unsigned int)fd < MAXFD - 1)

int open(const char *pathname, int flags, ... /* mode */);
int fcntl(int fd, int cmd, ... /* arg */ );
#define F_GETFL 1

#define AT_FDCWD                0x01
#define AT_EACCESS              0x02  /* Check access using effective user
#define AT_SYMLINK_NOFOLLOW     0x04  /* Do not follow symbolic links */
#define AT_SYMLINK_FOLLOW       0x08  /* Follow symbolic link */
#define AT_REMOVEDIR            0x10  /* Remove directory instead of file */
#define AT_EMPTY_PATH		0x20
#define AT_NO_AUTOMOUNT		0x40
#define AT_SYMLINK_NOFOLLOW	0x80

#endif
