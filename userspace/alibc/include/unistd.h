#ifndef _UNISTD_H
#define _UNISTD_H
#include <sys/types.h>

#define PATHMAX 256

int usleep(unsigned long usec);
#define switchtask usleep(1)
int execve(const char* file, char** iargv,  char** envp);
int execv(const char *pathname, char** iargv);
int execvp(const char *file, char** iargv);
int execlp(const char *file, /*const char *arg,*/ ... /*, (char *) NULL */);
int execl(const char *pathname, const char *arg, ... /*, (char *) NULL */);
int chdir(const char *path);
char *get_current_dir_name(void);
char *getcwd(char* buf, size_t size);
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
int lchown(const char *pathname, uid_t owner, gid_t group);
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
#define _SC_CLK_TCK 2
#define _SC_NGROUPS_MAX 3

ssize_t readlinkat(int dirfd, const char* pathname, char* buf, size_t bufsiz);
ssize_t readlink(const char* pathname, char* buf, size_t bufsiz);

pid_t setsid(void);

int dup(int oldfd);
int dup2(int oldfd, int newfd);

int pipe(int pipefd[2]);
int pipe2(int pipefd[2], int flags);

int access(const char *pathname, int mode);
int faccessat(int dirfd, const char *pathname, int mode, int flags);

int chroot(const char *path);

pid_t getpid(void);
pid_t getppid(void);

int gethostname(char *name, size_t len);

pid_t tcgetpgrp(int fd);
int tcsetpgrp(int fd, pid_t pgrp);

int setpgid(pid_t pid, pid_t pgid);
pid_t getpgid(pid_t pid);
pid_t getpgrp(void);

int setgroups(size_t size, const gid_t* list);
unsigned int alarm(unsigned int seconds);

int rmdir(const char *pathname);

char *ttyname(int fd);
int ttyname_r(int fd, char buf[], size_t buflen);

unsigned int sleep(unsigned int seconds);

#endif
