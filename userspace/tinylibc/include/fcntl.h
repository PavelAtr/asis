#ifndef _FCNTL_H
#define _FCNTL_H

#include <stdio.h>

#define O_CLOEXEC 0x0001
#define O_RDONLY 0x0002
#define O_RDWR 0x0004
#define O_WRONLY 0x0008
#define O_CREAT 0x0010
#define O_TRUNC 0x0020
#define O_APPEND 0x0040
#define O_EXCL 0x0080
#define O_ACCMODE 0x0100
#define O_NOFOLLOW 0x0200
#define O_NONBLOCK 0x0400
#define O_SYNC 0x0800

#define O_NOCTTY 00000400 

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
  pid_t pgrp;
  pipebuf* wpipe;
  pipebuf* rpipe;
} fdesc;

static inline void copyfdesc(fdesc* dst, fdesc* src)
{
   if (!src->stream) {
      return;
   }
   memcpy(dst, src, sizeof(fdesc));
   dst->stream = malloc(sizeof(FILE));
   copyfile(dst->stream, src->stream);
   if (src->wpipe) {
      src->wpipe->nlink++;
   }
   if (src->rpipe) {
      src->rpipe->nlink++;
   }
}

static inline void freefdesc(fdesc* dst)
{
   if (!dst) {
      return;
   }
   freefile(dst->stream);
   dst->stream = NULL;;
   if (dst->rpipe) {
      dst->rpipe->nlink--;
      if (dst->rpipe->nlink == 0) {
         free(dst->rpipe);
         dst->rpipe = NULL;         
      }
   }
   if (dst->wpipe) {
      dst->wpipe->nlink--;
      if (dst->wpipe->nlink == 0) {
         free(dst->wpipe);
         dst->wpipe = NULL;
      }
   }
   free(dst);
}

extern unsigned int MAXFD;
extern fdesc** fds;
int get_free_fd(void);
#define fd_is_valid(fd) (fds[fd] && (unsigned int)fd < MAXFD - 1)

int open(const char *pathname, int flags, ... /* mode */);
int creat(const char *pathname, mode_t mode);
#define open64 open
int fcntl(int fd, int cmd, ... /* arg */ );
#define F_GETFL 1
#define F_GETFD 2
#define F_SETFD 3
#define F_SETLK 4
#define F_SETFL 5
#define F_DUPFD 6

#define FD_CLOEXEC 1

#define AT_FDCWD                0x01
#define AT_EACCESS              0x02  /* Check access using effective user
#define AT_SYMLINK_NOFOLLOW     0x04  /* Do not follow symbolic links */
#define AT_SYMLINK_FOLLOW       0x08  /* Follow symbolic link */
#define AT_REMOVEDIR            0x10  /* Remove directory instead of file */
#define AT_EMPTY_PATH		0x20
#define AT_NO_AUTOMOUNT		0x40
#define AT_SYMLINK_NOFOLLOW	0x80
int openat(int dirfd, const char *pathname, int flags, ... /* mode */);

struct flock
  {
    short int l_type;   /* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.  */
    short int l_whence; /* Where `l_start' is relative to (like `lseek').  */
#ifndef __USE_FILE_OFFSET64
    off_t l_start;    /* Offset where the lock begins.  */
    off_t l_len;      /* Size of the locked area; zero means until EOF.  */
#else
    off64_t l_start;  /* Offset where the lock begins.  */
    off64_t l_len;    /* Size of the locked area; zero means until EOF.  */
#endif
    pid_t l_pid;      /* Process holding the lock.  */
  };

#define F_RDLCK         0
#define F_WRLCK         1
#define F_UNLCK         2

# define POSIX_FADV_NORMAL      0 /* No further special treatment.  */
# define POSIX_FADV_RANDOM      1 /* Expect random page references.  */
# define POSIX_FADV_SEQUENTIAL  2 /* Expect sequential page references.  */
# define POSIX_FADV_WILLNEED    3 /* Will need these pages.  */
# define POSIX_FADV_DONTNEED    4 /* Don't need these pages.  */
# define POSIX_FADV_NOREUSE     5 /* Data will be accessed once.  */


#endif
