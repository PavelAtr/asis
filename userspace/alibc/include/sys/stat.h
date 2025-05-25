#include <sys/types.h>
#include <time.h>

#ifndef _STAT_H
#define _STAT_H

#define S_IFMT     0170000
#define S_IFSOCK   0140000
#define S_IFLNK    0120000
#define S_IFREG    0100000
#define S_IFBLK    0060000
#define S_IFDIR    0040000
#define S_IFCHR    0020000
#define S_IFIFO    0010000

#define S_IRWXU  00700
#define S_IRUSR  00400
#define S_IWUSR  00200
#define S_IXUSR  00100
#define S_IRWXG  00070
#define S_IRGRP  00040
#define S_IWGRP  00020
#define S_IXGRP  00010
#define S_IRWXO  00007
#define S_IROTH  00004
#define S_IWOTH  00002
#define S_IXOTH  00001
#define S_ISUID  04000
#define S_ISGID  02000
#define S_ISVTX  01000
#define S_ISTXT  01000 

#define S_ISREG(mode) (mode & S_IFREG)
#define S_ISDIR(mode) (mode & S_IFDIR)
#define S_ISLNK(mode) (mode & S_IFLNK)
#define S_ISBLK(mode) (mode & S_IFBLK)
#define S_ISCHR(mode) (mode & S_IFCHR)
#define S_ISFIFO(mode) (mode & S_IFIFO)
#define S_ISSOCK(mode) (mode & S_IFSOCK)

struct stat {
  mode_t	st_mode;     /* File type and mode */
  uid_t	st_uid;      /* User ID of owner */
  gid_t	st_gid;      /* Group ID of owner */
  size_t	st_size;
  int st_nlink;
  short	st_major;
  short	st_minor;
  dev_t	st_dev;
  dev_t	st_rdev;
  long	st_ino;
  long st_blksize;
  long st_blocks;
  time_t      st_atime;
  time_t      st_mtime;
  time_t      st_ctime;
  struct  timespec st_atim;       /* time of last access */
  struct  timespec st_mtim;       /* time of last data modification */
  struct  timespec st_ctim;       /* time of last file status change */
  struct  timespec st_birthtim;   /* time of file creation */
};

int stat(const char* path, struct stat* statbuf);
int lstat(const char* pathname, struct stat* statbuf);
mode_t umask(mode_t mask);
#define gmask atoi(getenv("UMASK"))
int mknod(const char *pathname, mode_t mode, dev_t dev);
int mkdir(const char *pathname, mode_t mode);
int chmod(const char *pathname, mode_t mode);
int fstat(int fd, struct stat *statbuf);
int fstatat(int dirfd, const char* pathname,
                struct stat* statbuf, int flags);
int mkdirat(int dirfd, const char *pathname, mode_t mode);
int fchmodat(int dirfd, const char *pathname, mode_t mode, int flags);
int fchmod(int fd, mode_t mode);
int fchown(int fd, uid_t owner, gid_t group);

#define fstat64 fstat
#define lstat64 lstat
#define stat64 stat

#endif
