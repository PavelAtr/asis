#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef UEFI_KERNEL
long __attribute__((ms_abi)) (*syscall)(long number, ...);
void __attribute__((ms_abi)) (*retexit)(int ret);
#else
long (*syscall)(long num, ...);
void (*retexit)(int ret);
#endif
fdesc** fds = NULL;
char** environ = NULL;
int errno;
char* progname;
FILE* stdin;
FILE* stdout;
FILE* stderr;
FILE* dbpasswd = NULL;
FILE* dbgroup = NULL;
void (*atexit_func)(void) = NULL;

int main(int argc, char** argv);

void _start(int argc, char** argv, char** envp)
{
   environ = envp;
   stdin = fdopen(0, "r");
   stdout = fdopen(1, "w");
   stderr = fdopen(2, "w");
   progname = argv[0];
   int ret = main(argc, argv);
   _exit(ret);
}

void _exit(int status)
{
   if (atexit_func) {
      atexit_func();
   }
   retexit(status);
}
