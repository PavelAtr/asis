#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdarg.h>
#include <syscall.h>

FILE*** core_fds;
char*** core_environ;
char*** core_argv;
int errno;

long (*sys_syscall)(long number, va_list args);

long syscall(long number, ...)
{
   va_list vl;
   va_start(vl, number);
   long ret = sys_syscall(number, vl);
   errno = sys_syscall(SYS_GETERRNO, NULL);
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

