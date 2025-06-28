#include <syscall.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int execlp(const char *file, const char *arg, ...
                       /*, (char *) NULL */)
{
   va_list vl, vl2;
   va_start(vl, file);
   va_copy(vl2, vl);
   int i;
   for (i = 0; va_arg(vl, char*); i++);
   char** argv = malloc(i * sizeof(char*));
   char* a;
   for (i = 0; (a = va_arg(vl2, char*)); i++);
	argv[i] = a;
   argv[i] = NULL;
    return execve(file, argv, NULL);
}

int execl(const char *pathname, const char *arg, ... /*, (char *) NULL */) __attribute__((alias("execlp")));
