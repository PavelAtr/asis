#ifndef _LIBDL_H
#define _LIBDL_H

#include "tinyelf.h"
#include "namedlist.h"
#include <sys/types.h>

#define LD_PATH "/tinysys/usr/lib/:/tinysys/lib/"

typedef struct {
   Elf_Shdr* head;
   Elf_Sym* syms;
   char* symstr;
   char dynamic;
} elfsyms;

typedef struct {
   Elf_Shdr* head;
   Elf_Rela* relas;
} elfrelas;

typedef struct {
   Elf_Rela* relas;
   int count;
} tlsrelas;

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
   size_t tls_size;
   char* exec;
   unsigned long tls_index;
} elf;

typedef struct {
   const char* path;
   elf* dl_elf;
   int flags;
   int status;
   int nlink;
} dl;

typedef struct {
   NAMED_LIST_ESSENTIAL
   dl* obj;
} dlhandle;

/* sl->status field */
#define DL_RELOCATED 0x01
#define DL_INITED 0x02

#endif
