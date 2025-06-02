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
   return asyscall(SYS_TLSADDR, ti_module, ti_offset, 0, 0, 0, 0);
}
   
