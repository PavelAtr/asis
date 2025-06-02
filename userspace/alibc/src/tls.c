#include <syscall.h>
#include <stdio.h>

#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
extern void* (*sys_syscall)(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);


typedef struct
{
   unsigned long int ti_module;
   unsigned long int ti_offset;
} tls_index;

void* __tls_get_addr (tls_index *ti)
{
   unsigned long ti_module = ti->ti_module;
   unsigned long ti_offset = ti->ti_offset;
   return sys_syscall(SYS_TLSADDR, (void*)ti_module, (void*)ti_offset, NULL, NULL, NULL, NULL);
}
   
