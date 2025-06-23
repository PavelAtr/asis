#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syscall.h>
#include <start.h>

int main(int argc, char** argv);
void libtinyc_init(int* cerrno, char*** cargv, char*** cenviron, FILE*** cfds, void* csyscall, void* cretexit, char*** cdtv);

int _start(startarg* arg)
{
   libtinyc_init(arg->cerrno, arg->cargv, arg->cenvp, (FILE***)arg->cfds,
                  arg->syscall_func, arg->retexit_func, arg->cdtv);
   int ret = main(arg->argc, *arg->cargv);
   _exit(ret);

/* Not reacheble */
   return ret;
}
