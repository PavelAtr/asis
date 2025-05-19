#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void
#ifdef UEFI_KERNEL
__attribute__((ms_abi))
#endif
(*retexit)(int ret);

void _exit(int status)
{
    if (atexit_func) {
        atexit_func();
    }
    retexit(status);
    while (1); // Гарантирует, что функция не вернёт управление
}
