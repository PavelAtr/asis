#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

char* origin = "hello"; /* GARBAGE */

extern __thread int test;

void _atexit(void)
{
}

int main(int argc, char** argv)
{
   errno = ENOTSUP;
   printf("TEST\n");
   puts("TEST2\n");
   printf("progname=%s\n", getprogname());
   printf("test=%d\n", test);
   test = 1;
   printf("test=%d\n", test);
   void* ptr = malloc(100);
   printf("malloc(100)=%p\n", ptr);
   size_t size = fprintf(stdout, "s=%s d=%d f=%f strlen(5)=%d\n", "string", 1000,
         1.0156, strlen("12345"));
   printenv();
   atexit(&_atexit);
   return size;
}
