#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <syscall.h>

char quiet = 0;

int errno;
FILE*** core_fds;
char*** core_dtv;
char*** core_environ;
char*** core_argv;
int* core_errno;
#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
void* (*syscall)(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);

void libtinyc_init(int* cerrno, char*** cargv, char*** cenviron, FILE*** cfds, void* csyscall, void* cretexit, char*** cdtv)
{
   quiet = 1; // Disable debug output by default
   core_dtv = cdtv;
   syscall = csyscall;
   retexit = cretexit;
   core_fds = cfds;
   core_environ = cenviron;
   core_argv = cargv;
   core_errno = cerrno;
   quiet = 0; // Enable debug output
}

