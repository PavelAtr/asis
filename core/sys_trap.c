#include <asis.h>
#include <stddef.h>

void trap_segfault()
{
   sys_printf(SYS_ERROR "SEGFAULT at pid=%d\n", curpid);
   sys_printf(SYS_DEBUG "SEGFAULT stack=%p sp=%p depth=%ld\n", current->ctx.stack, sp, sp - current->ctx.stack);
   freeproc(curpid);
   switch_context;
}
