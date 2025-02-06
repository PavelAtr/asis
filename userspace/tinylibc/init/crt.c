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
FILE* dbpasswd = NULL;
FILE* dbgroup = NULL;
void (*atexit_func)(void) = NULL;

int main(int argc, char** argv);
void libtinyc_init(FILE** fds, char** environ, char** argv, errno_t** errno);

int _start(int argc, char** argv, char** envp, FILE** cfds, errno_t** errno, void* syscall_func, void* retexit_func)
{
   syscall = syscall_func;
   retexit = retexit_func;
   libtinyc_init(cfds, envp, argv, errno);
   int ret = main(argc, argv);
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
