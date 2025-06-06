#ifndef _DLFCN_H
#define _DLFCN_H


void *dlopen(const char* filename, int flags);
void *dlsym(void* handle, const char* symbol);
int dlclose(void* handle);

#endif
