#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

pid_t fork(void)
{
    FILE** proc_afds = afds;
    char** proc_environ = environ;
    char** proc_argv = aargv;

   pid_t ret = vfork();

    afds = proc_afds;
    environ =  proc_environ;
    aargv = proc_argv;

   return ret;
}
