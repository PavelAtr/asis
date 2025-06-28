#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

FILE** copyfds(FILE** fds);
char** copyenv(char** e);

__thread char need_copy_fds = 0;

pid_t fork(void)
{
    FILE** proc_afds = afds;
    char** proc_environ = environ;
    char** proc_argv = aargv;
   
   pid_t ret = (pid_t)asyscall(SYS_FORK, 0, 0, 0, 0, 0, 0);

    if (ret == 0) {
         afds = proc_afds;
         afds = copyfds(proc_afds);
         asyscall(SYS_SETFDS, afds, 0, 0, 0, 0, 0);
         environ =  copyenv(proc_environ);
	      asyscall(SYS_SETENVIRON, environ, proc_environ, 0, 0, 0, 0);
         printenv();
         aargv = proc_argv;
         need_copy_fds = 0;
    }
   return ret;
}

pid_t vfork(void)
{
    FILE** proc_afds = afds;
    char** proc_environ = environ;
    char** proc_argv = aargv;

   pid_t ret = (pid_t)asyscall(SYS_VFORK, 0, 0, 0, 0, 0, 0);

    if (ret == 0) {
         afds = proc_afds;
         environ =  copyenv(proc_environ);
	      asyscall(SYS_SETENVIRON, environ, 0, 0, 0, 0, 0);
         aargv = proc_argv;
         need_copy_fds = 1;
    }

   return ret;
}
