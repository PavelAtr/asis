#include <asis.h>
#include "../userspace/libdl/dlfcn.h"

void* sys_dlopen(const char *filename, int flags)
{
    void* handle;	
    handle = dlopen(filename, 0);
    return handle;
}


int sys_dlclose(void *handle)
{
   if (!handle) {
	  return -1;
   }
   return dlclose(handle);
}

void* sys_dlsym(void * handle, const char * symbol)
{
	return dlsym(handle, symbol);
}

extern void** current_fds;

void sys_dltls(void* handle, unsigned long module_id)
{
	sys_printf(SYS_DEBUG "Set TLS modid=%ld in %p\n", module_id, handle);
	dltls(handle, module_id);
}
