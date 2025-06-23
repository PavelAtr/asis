#ifndef _DLFCN_H
#define _DLFCN_H

#define RTLD_LAZY 0x01
#define RTLD_LOCAL 0x02
#define RTLD_NOW 0x04
#define RTLD_GLOBAL 0x08

typedef struct {
    const char *dli_fname;  /* Pathname of shared object that
                            contains address */
    void       *dli_fbase;  /* Base address at which share
                            object is loaded */
    const char *dli_sname;  /* Name of symbol whose definition
                                overlaps addr */
    void       *dli_saddr;  /* Exact address of symbol named
                                in dli_sname */
} Dl_info;

void *dlopen(const char* filename, int flags);
void *dlsym(void* handle, const char* symbol);
int dlclose(void* handle);
int dladdr(const void *addr, Dl_info *info);
char *dlerror(void);

#endif
