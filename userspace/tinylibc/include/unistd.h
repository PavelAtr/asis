#ifndef _UNISTD_H
#define _UNISTD_H
#include <sys/types.h>

#define PATHMAX 256

int usleep(unsigned long usec);
int execve(const char* file, char* const * argv,  char* const * envp);

extern char cwd[PATHMAX];
int chdir(const char *path);
char *get_current_dir_name(void);
char* fullpath(const char* dir, const char* path);
char* execpath(const char* path, const char* file);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

off_t lseek(int fd, off_t offset, int whence);
ssize_t write(int f, const void* buf, size_t count);
ssize_t read(int f, void* buf, size_t count);
int close(int fd);
int truncate(const char *path, off_t length);
int unlink(const char *pathname);
int setuid(uid_t uid);
int setgid(gid_t gid);

uid_t getuid(void);
gid_t getgid(void);
#define geteuid getuid
#define getegid getgid

int chown(const char *pathname, uid_t owner, gid_t group);
pid_t fork(void);
pid_t vfork(void);
int symlink(const char *target, const char *linkpath);
int link(const char *oldpath, const char *newpath);
void _exit(int status);

/* Standard file descriptors.  */
#define STDIN_FILENO    0       /* Standard input.  */
#define STDOUT_FILENO   1       /* Standard output.  */
#define STDERR_FILENO   2       /* Standard error output.  */

#define R_OK    4               /* Test for read permission.  */
#define W_OK    2               /* Test for write permission.  */
#define X_OK    1               /* Test for execute permission.  */
#define F_OK    0               /* Test for existence.  */

int isatty(int fd);

int fsync(int fd);
#define fdatasync(fd) fsync(fd)
ssize_t pread(int fd, void* buf, size_t count, off_t offset);
ssize_t pwrite(int fd, const void* buf, size_t count, off_t offset);
int ftruncate(int fd, off_t length);

long sysconf(int name);
#define _SC_OPEN_MAX 1

ssize_t readlinkat(int dirfd, const char* pathname, char* buf, size_t bufsiz);

#endif
