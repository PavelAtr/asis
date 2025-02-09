#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

FILE*** core_fds;
char*** core_environ;
char*** core_argv;
int** core_errno;

#ifdef UEFI_KERNEL
long __attribute__((ms_abi)) (*syscall)(long number, ...);
#else
long (*syscall)(long num, ...);
#endif


void libtinyc_init(FILE*** cfds, char*** cenviron, char*** cargv, int** cerrno, void* csyscall, void* cretexit)
{
   core_fds = cfds;
   core_environ = cenviron;
   core_argv = cargv;
   core_errno = cerrno;
   syscall = csyscall;
   retexit = cretexit;
}

