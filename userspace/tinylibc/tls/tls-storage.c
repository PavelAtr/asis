#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

__thread FILE** core_fds;
__thread char** core_environ;
__thread char** core_argv;
errno_t** core_errno;

void libtinyc_init(FILE** cfds, char** cenviron, char** cargv, errno_t** cerrno)
{
   core_fds = cfds;
   core_environ = cenviron;
   core_argv = cargv;
   core_errno = cerrno;
}

