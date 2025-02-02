#ifdef DEBUG
#include "include/tinysys.h"
#include <dlfcn.h>
#else
#include <tinysys.h>
#include "libdl/libdl.h"
#endif

void* sys_dlopen(const char *filename, int flags)
{
	return dlopen(filename, RTLD_NOW | RTLD_DEEPBIND);
}

int sys_dlclose(void *handle)
{
	return dlclose(handle);
}

void* sys_dlsym(void * handle, const char * symbol)
{
	return dlsym(handle, symbol);
}

