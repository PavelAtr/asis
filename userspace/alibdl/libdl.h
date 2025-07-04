#ifndef _LIBDL_H
#define _LIBDL_H

#include "tinyelf.h"
#include "list.h"
#include <sys/types.h>

extern char * ld_library_path;

#define LD_LIBRARY_PATH "/lib:/usr/lib"

typedef struct {
   Elf_Shdr* head;
   Elf_Rela* relas;
} elfrelas;

typedef struct {
   Elf_Ehdr* hdr;
   Elf_Phdr* phdrs;
   Elf_Shdr* shdrs;
   elfrelas** rela;
   Elf_Shdr* dynsym_hdr;
   Elf_Sym* dynsym_tab;
   char* dynsym_str;
   Elf_Shdr* symtab_hdr;
   Elf_Sym* symtab_tab;
   char* symtab_str;
   Elf_Shdr* dyns;
   Elf_Dyn* dyntab;
   char* dynstr;
   char* shstr;
   size_t exec_size;
   char* tls_initaddr;
   size_t tls_size;
   char* exec;
} elf;

typedef struct {
   const char* path;
   elf* dl_elf;
   int flags;
   int status;
   int nlink;
   size_t tls_size;
   unsigned int module_id;
} dl;

typedef struct {
   NAMED_LIST_ESSENTIAL
   dl* obj;
} dlhandle;

/* sl->status field */
#define DL_RELOCATED 0x01
#define DL_INITED 0x02
void elf_relocate_tls(Elf_Shdr* rela, Elf_Rela* relatab, dl* s, Elf_Sym* (*resolve2)(const char *symname, dl** out));
void tls_init(dl* s, char* dest, size_t tls_size);


#endif
