#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <syscall.h>

char quiet = 0;

int errno;
__thread char** aargv;

__thread int test = 10;

#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
void* (*sys_syscall)(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);

void* syscall(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6)
{
   void* ret = sys_syscall(number, arg1, arg2, arg3, arg4 , arg5, arg6);
   errno = (int)sys_syscall(SYS_GETERRNO, 0, 0, 0, 0, 0, 0);
   return ret;
}

extern char** dtv;

void libtinyc_init(char** cargv, char** cenviron, FILE** cfds, void* csyscall, void* cretexit, char** cdtv)
{
   quiet = 1; // Disable debug output by default
   if (cdtv) dtv = cdtv;
   if (csyscall) sys_syscall = csyscall;
   if (cretexit) retexit = cretexit;
   if (cfds) fds = cfds;
   if (cenviron) environ = cenviron;
   if (cargv) aargv = cargv;
   quiet = 0; // Enable debug output
}

