#include <syscall.h>
#include <stdio.h>

typedef struct
{
   unsigned long int ti_module;
   unsigned long int ti_offset;
} tls_index;

void* __tls_get_addr (tls_index *ti)
{
   unsigned long ti_module = ti->ti_module;
   unsigned long ti_offset = ti->ti_offset;
   return syscall(SYS_TLSADDR, (void*)ti_module, (void*)ti_offset, NULL, NULL, NULL, NULL);
}
   
