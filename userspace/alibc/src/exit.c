#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

__thread void (*atexit_func)(void) = (void*)0x1;

int atexit(void (*function)(void))
{
   atexit_func = function;
   return 0;
}

#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
void (*retexit)(int ret);

void freeenv(char** e)
{
   if (!e) {
      return;
   }
   int argc;
	for (argc = 0; e[argc]; argc++){
      if (e[argc]) {
         free(e[argc]);
      }
   }
   free((void*)e);
}

void _exit(int status)
{
    if (atexit_func == (void*)0x1) {
        atexit_func = NULL; // Удаляем фиктивное значение
    }
    if (atexit_func) {
         atexit_func();
    }
    freeenv(environ);
    retexit(status);
    while (1); // Гарантирует, что функция не вернёт управление
}
