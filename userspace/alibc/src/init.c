#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <syscall.h>

char quiet = 0;

__thread FILE** afds;
__thread char** environ;
__thread char** aargv;
__thread int errno;
#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
void* (*syscall)(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);

#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
extern void (*retexit)(int ret);


void libtinyc_init(char** cargv, char** cenviron, void** cfds, void* csyscall, void* cretexit)
{

   quiet = 1; // Disable debug output by default
   syscall = csyscall;
   retexit = cretexit;
   afds = (FILE**)cfds;
   environ = cenviron;
   aargv = cargv;
   quiet = 0; // Enable debug output
}

