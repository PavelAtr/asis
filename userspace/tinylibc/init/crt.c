#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>




#ifdef UEFI_KERNEL
long __attribute__((ms_abi)) (*syscall)(long number, ...);
void __attribute__((ms_abi)) (*atexit)(int ret);
#else
long (*syscall)(unsigned int num, ...);
void (*atexit)(int ret);
#endif
fdesc* fds = NULL;
char** environ = NULL;
int errno;
char* progname;
char cwd[PATHMAX] = {'/', '\0'};
FILE* stdin;
FILE* stdout;
FILE* stderr;
FILE* dbpasswd = NULL;
FILE* dbgroup = NULL;

int main(int argc, char** argv);

void _start(int argc, char** argv, char** envp)
{
   environ = envp;
   stdin = fdopen(0, "r");
   stdout = fdopen(1, "w");
   stderr = fdopen(2, "w");
   const char* cwd = getenv("CWD");
   if (cwd) {
      chdir(cwd);
   }
   const char* mask = getenv("UMASK");
   if (mask) {
      umask(atoi(mask));
   }
   progname = argv[0];
   int ret = main(argc, argv);
   atexit(ret);
}

void _exit(int status)
{
   atexit(status);
}
