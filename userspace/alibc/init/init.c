#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <syscall.h>

FILE*** core_fds;
char*** core_environ;
char*** core_argv;
int errno;

#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
long64_t (*sys_syscall)(int number, long64_t arg1, long64_t arg2, long64_t arg3, long64_t arg4, long64_t arg5, long64_t arg6);

long64_t syscall(int number, long64_t arg1, long64_t arg2, long64_t arg3, long64_t arg4, long64_t arg5, long64_t arg6)
{
   long ret = sys_syscall(number, arg1, arg2, arg3, arg4 , arg5, arg6);
   errno = sys_syscall(SYS_GETERRNO, 0, 0, 0, 0, 0, 0);
   return ret;
}

void libtinyc_init(FILE*** cfds, char*** cenviron, char*** cargv, void* csyscall, void* cretexit)
{
   core_fds = cfds;
   core_environ = cenviron;
   core_argv = cargv;
   sys_syscall = csyscall;
   retexit = cretexit;
}

