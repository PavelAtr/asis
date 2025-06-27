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

int _start(startarg* arg)
{
   libtinyc_init(arg->cargv, arg->cenvp, arg->cfds, arg->syscall_func, arg->retexit_func);
   int ret = main(arg->argc, arg->cargv);
   _exit(ret);

/* Not reacheble */
   return ret;
}
