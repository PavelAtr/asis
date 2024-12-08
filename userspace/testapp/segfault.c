#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <tiny.h>

int main(int argc, char** argv)
{
   stdout = NULL;
   size_t size = puts("Hello world!\n");
   puts("PATH=");
   puts(getenv("PATH"));
   puts("\n");
   char buf[12];
   int a;
   a = -123456789;
   int b;
   b = 1;
   int c;
   c = a + b;
   int len  = itoa(c, 10, buf);
   buf[len] = '\n';
   buf[len + 1] = '\0';
   size = puts(buf);
   return len;
}
