#include <syscall.h>
#include <stdio.h>

#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
extern void* (*sys_syscall)(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);

char** dtv;
void __tls_init(char** dtv_ptr)
{
   if (dtv_ptr == NULL) {
      return; // Invalid pointer
   }
   dtv = (char**)dtv_ptr;
}
typedef struct
{
   unsigned long int ti_module;
   unsigned long int ti_offset;
} tls_index;

extern char quiet;

#ifdef UEFI_KERNEL
__attribute__((ms_abi)) 
#endif
extern void* (*sys_syscall)(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6);

void* __tls_get_addr (tls_index *ti)
{
   unsigned long ti_module = ti->ti_module;
   unsigned long ti_offset = ti->ti_offset;
   void* ret = dtv[ti_module] + ti_offset;
   if (quiet) {
      return ret;
   }  
   char buf[150];
   sprintf(buf, "ti_module=%lu, ti_offset=%lu ret=", ti_module, ti_offset);
   sys_syscall(SYS_DBG, (void*)buf, ret, (void*)0, (void*)0, (void*)0, (void*)0);
   return ret;
}
   
