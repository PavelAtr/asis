#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef UEFI_KERNEL
long __attribute__((ms_abi)) (*syscall)(long number, ...);
void __attribute__((ms_abi)) (*retexit)(long ret);
#else
long (*syscall)(long num, ...);
void (*retexit)(int ret);
#endif
FILE*** core_fds = NULL;
char*** core_environ = NULL;
char*** core_argv = NULL;
int errno;
FILE* dbpasswd = NULL;
FILE* dbgroup = NULL;
void (*atexit_func)(void) = NULL;

int main(int argc, char** argv);

void _start(int argc, void* argv, void* envp, void* cfds, void* syscall_func, void* retexit_func)
{
   core_argv = argv;
   core_environ = envp;
   core_fds = cfds;
   syscall = syscall_func;
   retexit = retexit_func;
   int ret = main(argc, *core_argv);
   _exit(ret);
}

void _exit(int status)
{
   if (atexit_func) {
      atexit_func();
   }
   retexit(status);
}
