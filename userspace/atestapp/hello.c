#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char* origin = "hello"; /* GARBAGE */

void _atexit(void)
{
}

int main(int argc, char** argv)
{
   errno = ENOTSUP;
   printf("Hello\n");
   puts("Hello2\n");
   printf("progname=%s\n", getprogname());
   void* ptr = malloc(100);
   printf("malloc(100)=%p\n", ptr);
   size_t size = fprintf(stdout, "s=%s d=%d f=%f strlen(5)=%d\n", "string", 1000,
         1.0156, strlen("12345"));
   printenv();
   atexit(&_atexit);
    printf("sizeof(float)=%d\n", sizeof(float));
    printf("sizeof(double)=%d\n", sizeof(double));
    printf("sizeof(long double)=%d\n", sizeof(long double));
   return size;
}
