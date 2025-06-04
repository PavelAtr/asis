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
void libtinyc_init(char** cargv, char** cenviron, FILE*** cfds, void* csyscall, void* cretexit, char*** cdtv);
#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
extern void* (*sys_syscall)(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);



int _start(int argc, char** cargv, char** cenvp, FILE*** cfds, void* syscall_func, void* retexit_func, char*** cdtv)
{
   libtinyc_init(cargv, cenvp, cfds, syscall_func, retexit_func, cdtv);
   int ret = main(argc, cargv);
   _exit(ret);

/* Not reacheble */
   return ret;
}
