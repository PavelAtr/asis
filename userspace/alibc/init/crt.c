#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syscall.h>

FILE* dbpasswd;
FILE* dbgroup;

int main(int argc, char** argv);
void libtinyc_init(int* cerrno, char*** cargv, char*** cenviron, FILE*** cfds, void* csyscall, void* cretexit, char*** cdtv);

int _start(int argc, int* cerrno, char*** cargv, char*** cenvp, FILE*** cfds, void* syscall_func, void* retexit_func, char*** cdtv)
{
   libtinyc_init(cerrno, cargv, cenvp, cfds, syscall_func, retexit_func, cdtv);
   int ret = main(argc, *cargv);
   _exit(ret);

/* Not reacheble */
   return ret;
}
