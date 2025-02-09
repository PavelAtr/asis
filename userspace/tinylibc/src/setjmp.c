#include <setjmp.h>
#include <signal.h>
#include <syscall.h>

int setjmp(jmp_buf env)
{
   return syscall(SYS_SETJMP, env);
}

int sigsetjmp(sigjmp_buf env, int savesigs)
{
   env[0].__mask_was_saved = 1;
   env[0].__saved_mask = savesigs;
   return setjmp(env[0].__jmpbuf);
}

void longjmp(jmp_buf env, int val)
{
   syscall(SYS_LONGJMP, env);
}

void siglongjmp(sigjmp_buf env, int val)
{
   sigsetmask(env[0].__saved_mask);
   longjmp(env[0].__jmpbuf, val);
}
