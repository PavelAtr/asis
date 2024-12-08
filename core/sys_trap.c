#include <tinysys.h>
#include <stddef.h>

void trap_segfault()
{
  sys_printf(SYS_ERROR "SEGFAULT at pid=%d\n", curpid);
  freeproc(curpid);
  switch_context;
}
