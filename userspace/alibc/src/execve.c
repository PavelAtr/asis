#include <syscall.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

FILE** copyfds(FILE** infds);
FILE** cloexecfds(FILE** fds);
extern __thread char need_copy_fds;

int execve(const char* pathname, char * const* iargv, char * const* envp)
{
    char* path = execpath(getenv("PATH"), pathname);
    if (need_copy_fds) {
        afds = copyfds(afds);
        asyscall(SYS_SETFDS, afds, 0, 0, 0, 0, 0);
        afds = cloexecfds(afds);
        need_copy_fds = 0;
    }
    int err = (int)asyscall(SYS_EXECVE, path, iargv, envp, 0, 0, 0);
    errno = err;
    return err;
}

int execv(const char *pathname, char * const* iargv)
{
    return execve(pathname, iargv, NULL);
}

int execvp(const char *file, char * const* iargv)
{
    return execve(file, iargv, NULL);
}
