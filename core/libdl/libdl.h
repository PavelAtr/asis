#ifndef _LIBDL_H
#define _LIBDL_H

#include "tinyelf.h"

typedef struct {
  Elf_Ehdr* hdr;
  Elf_Phdr* phdrs;
  Elf_Shdr* shdrs;
  Elf_Shdr* rela1;
  Elf64_Rela* relatab1;
  Elf_Shdr* rela2;
  Elf64_Rela* relatab2;
  Elf_Shdr* syms;
  Elf_Sym* symtab;
  const char* symstr;
  Elf_Shdr* dynsyms;
  Elf_Sym* dynsymtab;
  const char* dynsymstr;
  Elf_Shdr* dyns;
  Elf64_Dyn* dyntab;
  const char* dynstr;
  len_t exec_size;
  char* exec;
} elf;

void *dlopen(const char* filename, int flags);
void *dlsym(void* handle, const char* symbol);
int dlclose(void *handle);

typedef struct {
  const char* path;
  elf* dl_elf;
  void* next;
  int_t nlink;
} dl;

#endif
