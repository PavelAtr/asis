#ifndef _SETJMP_H
#define _SETJMP_H

#include <signal.h>

typedef long int __jmp_buf[8];
typedef long int jmp_buf[8];

struct __jmp_buf_tag
  {
    /* NOTE: The machine-dependent definitions of `__sigsetjmp'
       assume that a `jmp_buf' begins with a `__jmp_buf' and that
       `__mask_was_saved' follows it.  Do not move these members
       or add others before it.  */
    __jmp_buf __jmpbuf;         /* Calling environment.  */
    int __mask_was_saved;       /* Saved the signal mask?  */
    sigset_t __saved_mask;    /* Saved signal mask.  */
  };


typedef struct __jmp_buf_tag sigjmp_buf[1];

int setjmp(jmp_buf env);
int sigsetjmp(sigjmp_buf env, int savesigs);
void longjmp(jmp_buf env, int val);
void siglongjmp(sigjmp_buf env, int val);

#endif