#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syscall.h>

int main(int argc, char** argv);
void libtinyc_init(FILE*** cfds, char*** cenviron, char*** cargv, void* csyscall, void* cretexit);


int
#ifdef UEFI_KERNEL
__attribute__((ms_abi))
#endif
_start(int argc, char*** cargv, char*** cenvp, FILE*** cfds, void* syscall_func, void* retexit_func)
{
   libtinyc_init(cfds, cenvp, cargv, syscall_func, retexit_func);
   int ret = main(argc, *cargv);
   _exit(ret);

/* Not reacheble */
   return ret;
}
