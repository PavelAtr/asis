#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
   size_t size = fprintf(stdout, "Hello world s=%s d=%d f=%f strlen(5)=%d\n", "string", 1000,
         1.0156, strlen("12345"));
   return size;
}
