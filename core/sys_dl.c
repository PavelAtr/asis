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
