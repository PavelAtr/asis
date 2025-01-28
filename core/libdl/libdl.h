#ifndef _LIBDL_H
#define _LIBDL_H

#include "tinyelf.h"

typedef struct {
   Elf_Ehdr* hdr;
   Elf_Phdr* phdrs;
   Elf_Shdr* shdrs;

   elfrelas** rela;
   elfsyms ** sym;


   Elf_Shdr* dyns;
   Elf_Dyn* dyntab;
   char* dynstr;
   len_t exec_size;
   char* exec;
} elf;

void *dlopen(const char* filename, int flags);
void *dlsym(void* handle, const char* symbol);
int dlclose(void *handle);

#define RTLD_NOW 0x0001
#define RTLD_LOCAL 0x0002
#define RTLD_DEEPBIND 0x0004

typedef struct {
   const char* path;
   elf* dl_elf;
   void* next;
} dl;

#endif
