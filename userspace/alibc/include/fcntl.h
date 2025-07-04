#ifndef _FCNTL_H
#define _FCNTL_H

#include <sys/types.h>
#include <limits.h>
#include <stdio.h>
#define COREMAXFD 20

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

int get_free_fd(void);
char fd_is_valid(int fd);

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
#define F_ADD_SEALS 7
#define F_SEAL_SHRINK 8
#define F_SEAL_SEAL 9
#define F_GET_SEALS 10

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

struct file_handle
{
  unsigned int handle_bytes;
  int handle_type;
  /* File identifier.  */
  unsigned char f_handle[0];
};

int name_to_handle_at(int dirfd, const char *pathname,
                 struct file_handle *handle,
                 int *mount_id, int flags);

int open_by_handle_at(int mount_fd, struct file_handle *handle,
                 int flags);

#endif
