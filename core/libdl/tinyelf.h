#ifndef _TINYELF_H
#define _TINYELF_H

#include "elf.h"
#include "../include/tinysys.h"

#ifdef ELF64
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Phdr Elf64_Phdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Rela Elf64_Rela
#define Elf_Sym Elf64_Sym
#define ELF_R_TYPE(r) ELF64_R_TYPE(r)
#define ELF_R_SYM(i) ELF64_R_SYM(i)
#define Elf_Xword Elf64_Xword
#define Elf_Dyn Elf64_Dyn
#endif

typedef struct {
   Elf_Shdr* head;
   Elf_Sym* syms;
   char* symstr;
   bool_t dynamic;
} elfsyms;

typedef struct {
   Elf_Shdr* head;
   Elf_Rela* relas;
} elfrelas;


Elf_Ehdr* elf_load_hdr(const char* path);
Elf_Phdr* elf_load_phdrs(const char* path, Elf_Ehdr* hdr);
len_t elf_load_exec(const char* path, Elf_Ehdr* hdr, Elf_Phdr* phdrs, char* exec);
Elf_Shdr* elf_load_shdrs(const char* path, Elf_Ehdr* hdr);
int_t elf_count_table(Elf_Ehdr* hdr, Elf_Shdr* shdrs, unsigned int sh_type);
Elf_Shdr* elf_find_table(Elf_Ehdr* hdr, Elf_Shdr* shdrs, int_t* start_ndx, unsigned int sh_type);
void* elf_load_table(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdr);
char* elf_load_strings(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdrs, Elf_Shdr* tab);
void* elf_symbol(Elf_Shdr* symhdr, Elf_Sym* symtab, const char* symstr, const char* exec, const char* symname);
extern int_t dtneed_ndx;
const char* elf_dtneed(Elf_Shdr* dynhdr, Elf64_Dyn* dyntab, const char* dynstr);
void elf_relocate(Elf_Ehdr* hdr, Elf_Shdr* rela, Elf_Rela* relatab, Elf_Sym* symtab, const char* symstr, Elf_Xword tls_offset, char* exec, void* (*resolve)(const char* symname));

#endif
