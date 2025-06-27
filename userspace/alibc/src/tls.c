#include <syscall.h>
#include <stdio.h>

typedef struct
{
   unsigned long int ti_module;
   unsigned long int ti_offset;
} tls_index;

extern void* (*sys_syscall)(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);

void* __tls_get_addr (tls_index *ti)
{
   unsigned long ti_module = ti->ti_module;
   unsigned long ti_offset = ti->ti_offset;
   return asyscall(SYS_TLS, ti_module, ti_offset, (void*)0, (void*)0, (void*)0, (void*)0);
}
   
