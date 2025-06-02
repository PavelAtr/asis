#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <syscall.h>

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

void libtinyc_init(FILE** cfds, char** cenviron, char** cargv, void* csyscall, void* cretexit)
{
   sys_syscall = csyscall;
   retexit = cretexit;

   fds = cfds;
   environ = cenviron;
   aargv = cargv;
   errno = 0;
   printf("libtinyc_init called %p\n", sys_syscall);
}

