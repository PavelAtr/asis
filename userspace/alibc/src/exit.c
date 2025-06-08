#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

__thread void (*atexit_func)(void) = (void*)0x1;

int atexit(void (*function)(void))
{
   atexit_func = function;
   return 0;
}

void (*retexit)(int ret);

void _exit(int status)
{
    if (atexit_func == (void*)0x1) {
        atexit_func = NULL; // Удаляем фиктивное значение
    }
    if (atexit_func) {
         atexit_func();
    }
    retexit(status);
    while (1); // Гарантирует, что функция не вернёт управление
}
