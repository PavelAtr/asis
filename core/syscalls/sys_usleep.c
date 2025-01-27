#include <tinysys.h>

#ifndef UEFI

#include <unistd.h>

#endif

int sys_usleep(long_t usec)
{
   sys_printf("USLEEP pid=%d prog=%s\n", current->pid, current->argv[0]);
   switch_context;
   return  0;
}
