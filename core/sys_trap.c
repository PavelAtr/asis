#include "include/asis.h"
#include <stddef.h>
#include <stdio.h>

void trap_segfault()
{
   char str[64];
   size_t size = sprintf(str, SYS_ERROR "SEGFAULT at pid=%d\n", curpid);
   fwrite(str, 1, size, stderr);
   sys_printf(SYS_DEBUG "SEGFAULT stack=%p sp=%p depth=%ld\n", current->ctx.stack, sp, sp - current->ctx.stack);
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ENDED;
   current->flags |= PROC_DESTROYED;
   switch_context;
}
