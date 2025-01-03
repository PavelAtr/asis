#include <setjmp.h>

/* NOT REALIZED */


int setjmp(jmp_buf env)
{
   return 0;
}

int sigsetjmp(sigjmp_buf env, int savesigs)
{
   return 0;
}

void longjmp(jmp_buf env, int val)
{
}

void siglongjmp(sigjmp_buf env, int val)
{
}
