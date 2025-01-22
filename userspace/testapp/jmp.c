#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void function(void)
{
   setjmp(env);
   puts("Jump!\n");
}

void function2(void)
{
   longjmp(env, 1);
}

int main(int argc, char** argv)
{
   function();
   function2();

   return 0;
}
