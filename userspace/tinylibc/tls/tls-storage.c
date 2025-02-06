#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

FILE*** core_fds;
__thread char** core_environ;
__thread char** core_argv;
errno_t** core_errno;

void libtinyc_init(char** cenviron, char** cargv)
{
   core_environ = cenviron;
   core_argv = cargv;
}

#ifdef UEFI_KERNEL
long __attribute__((ms_abi)) (*syscall)(long number, ...);
#else
long (*syscall)(long num, ...);
#endif
