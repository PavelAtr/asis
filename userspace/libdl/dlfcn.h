#ifndef _LIBDL_H
#define _LIBDL_H

#include "tinyelf.h"
#include "namedlist.h"
#include <sys/types.h>

#define LD_PATH "/tinysys/usr/lib/:/tinysys/lib/"

typedef struct {
   Elf_Ehdr* hdr;
   Elf_Phdr* phdrs;
   Elf_Shdr* shdrs;
   elfrelas** rela;
   tlsrelas** tlsrela;
   elfsyms ** sym;
   Elf_Shdr* dyns;
   Elf_Dyn* dyntab;
   char* dynstr;
   size_t exec_size;
   char* exec;
   unsigned long tls_index;
} elf;

void *dlopen(const char* filename, int flags);
void *dlsym(void* handle, const char* symbol);
int dlclose(void* handle);
void dltls(void* handle, unsigned long module_id);

#define RTLD_NOW 0x0001
#define RTLD_LOCAL 0x0002
#define RTLD_DEEPBIND 0x0004

typedef struct {
   NAMED_LIST_ESSENTIAL
   const char* path;
   elf* dl_elf;
   int flags;
   int nlink;
} dl;

#endif
