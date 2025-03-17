#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

FILE*** core_fds;
char*** core_environ;
char*** core_argv;
int errno;

#ifdef UEFI_KERNEL
long __attribute__((ms_abi)) (*sys_syscall)(long number, va_list args);
#else
long (*sys_syscall)(long number, va_list args);
#endif

void libtinyc_init(FILE*** cfds, char*** cenviron, char*** cargv, void* csyscall, void* cretexit)
{
   core_fds = cfds;
   core_environ = cenviron;
   core_argv = cargv;
   sys_syscall = csyscall;
   retexit = cretexit;
}

