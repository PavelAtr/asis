#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#ifdef UEFI_KERNEL
long __attribute__((ms_abi)) (*syscall)(long number, ...);
void __attribute__((ms_abi)) (*retexit)(long ret);
#else
long (*syscall)(long num, ...);
void (*retexit)(int ret);
#endif
FILE* dbpasswd = NULL;
FILE* dbgroup = NULL;
void (*atexit_func)(void) = NULL;

int main(int argc, char** argv);
void libtinyc_init(char** environ, char** argv);

int _start(int argc, char** cargv, char** cenvp, FILE*** cfds, errno_t** cerrno, void* syscall_func, void* retexit_func)
{
   syscall = syscall_func;
   retexit = retexit_func;
   core_fds = cfds;
   core_errno = cerrno;
   libtinyc_init(cenvp, cargv);
   int ret = main(argc, cargv);
   _exit(ret);

/* Not reacheble */
   return ret;
}

void _exit(int status)
{
   if (atexit_func) {
      atexit_func();
   }
   retexit(status);
}
