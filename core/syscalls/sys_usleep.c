#include "../../config.h"
#include <asis.h>

#ifdef CONFIG_LINUX
#include <unistd.h>
#endif

int sys_usleep(long_t usec)
{
   sys_printf(SYS_DEBUG "USLEEP pid=%d prog=%s\n", current->pid, current->argv[0]);
   switch_context;
   return  0;
}
