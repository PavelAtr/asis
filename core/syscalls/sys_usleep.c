#include <tinysys.h>

#ifndef UEFI

#include <unistd.h>

#endif

int sys_usleep(long_t usec)
{
   sys_printf(SYS_DEBUG "USLEEP pid=%d prog=%s\n", current->pid, current->program->argv[0]);
   switch_context;
   return  0;
}
