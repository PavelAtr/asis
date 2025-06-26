#include "include/asis.h"
#include "../config.h"
#undef printf

#ifdef CONFIG_LINUX
#include <stddef.h>
#include <stdio.h>
#endif

#ifdef CONFIG_UEFI
#include "uefi/uefi.h"
#endif

void trap_segfault()
{
   char str[64];
   size_t size = sprintf(str, SYS_ERROR "SEGFAULT at pid=%d\n", curpid);
#ifdef CONFIG_LINUX
   fwrite(str, 1, size, stderr);
#endif
#ifdef CONFIG_UEFI
   printf(str);
#endif
   sys_printf(SYS_DEBUG "SEGFAULT stack=%p sp=%p depth=%ld\n", current->ctx.stack, sp, sp - current->ctx.stack);
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ENDED;
   current->flags |= PROC_DESTROYED;
   switch_context;
}
