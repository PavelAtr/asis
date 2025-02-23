#ifdef DEBUG
#include "include/tinysys.h"
#include <dlfcn.h>
#else
#include <tinysys.h>
#include "../userspace/libdl/dlfcn.h"
#endif

void* sys_dlopen(const char *filename, int flags)
{
    void* handle;	
#ifdef DEBUG
	handle = dlopen(filename, RTLD_NOW | RTLD_DEEPBIND);
#else
	handle = dlopen(filename, 0);
#endif
    sys_printf(SYS_DEBUG "DLOPEN=%p\n", handle);
    return handle;
}


int sys_dlclose(void *handle)
{
	sys_printf(SYS_DEBUG "DLCLOSE=%p\n", handle);
#ifndef DEBUG
   return dlclose(handle);
#else
   return 0;
#endif
}

void* sys_dlsym(void * handle, const char * symbol)
{
	return dlsym(handle, symbol);
}

extern void** current_fds;

void sys_dltls(void* handle, unsigned long module_id)
{
	sys_printf(SYS_DEBUG "Set TLS modid=%ld in %p\n", module_id, handle);
#ifdef DEBUG
	if (current->tlsid) {
	   *current->tlsid = (addr_t)&curpid;
	}
#else
	dltls(handle, module_id);
#endif
}
