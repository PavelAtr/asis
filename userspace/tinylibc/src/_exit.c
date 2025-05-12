#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef UEFI_KERNEL
void __attribute__((ms_abi)) (*retexit)(int ret);
#else
void (*retexit)(int ret);
#endif

void _exit(int status)
{
    if (atexit_func) {
        atexit_func();
    }
    retexit(status);
    while (1); // Гарантирует, что функция не вернёт управление
}
