#ifdef DEBUG
#include "include/tinysys.h"
#include <dlfcn.h>
#else
#include <tinysys.h>
#include "../userspace/libdl/dlfcn.h"
#endif

#ifdef DEBUG
void* sys_dlopen(const char *filename, int flags)
{
	return dlopen(filename, RTLD_LOCAL | RTLD_NOW | RTLD_DEEPBIND);
}
#else
void* sys_dlopen(const char *filename, int flags)
{
	return dlopen(filename, 0);
}
#endif

int sys_dlclose(void *handle)
{
	return dlclose(handle);
}

void* sys_dlsym(void * handle, const char * symbol)
{
	return dlsym(handle, symbol);
}

extern void** current_fds;

void sys_dltls(void* handle, unsigned long module_id)
{
	sys_printf(SYS_DEBUG "Set TLS modid=%ld\n", module_id);
#ifdef DEBUG
	if (current->tlsid) {
	   *current->tlsid = (addr_t)&curpid;
	}
#else
	dltls(handle, module_id);
#endif
}
