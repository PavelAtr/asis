#ifndef _TINYELF_H
#define _TINYELF_H

#include "elf.h"
#include <sys/types.h>

#ifndef MARK
#define MARK "dldebug:\t"
#endif

#ifdef STANDALONE
typedef long long_t;
typedef long addr_t;
#endif

/* #ifdef ELF64 MARK*/
#define Elf_Ehdr Elf64_Ehdr
#define Elf_Phdr Elf64_Phdr
#define Elf_Shdr Elf64_Shdr
#define Elf_Rela Elf64_Rela
#define Elf_Sym Elf64_Sym
#define ELF_R_TYPE(r) ELF64_R_TYPE(r)
#define ELF_R_SYM(i) ELF64_R_SYM(i)
#define Elf_Xword Elf64_Xword
#define Elf_Dyn Elf64_Dyn
/*#endif MARK*/

Elf_Ehdr* elf_load_hdr(const char* path);
Elf_Phdr* elf_load_phdrs(const char* path, Elf_Ehdr* hdr);
size_t elf_load_exec(const char* path, Elf_Ehdr* hdr, Elf_Phdr* phdrs, char* exec, size_t* tls_size, char** tls_initaddr);
Elf_Shdr* elf_load_shdrs(const char* path, Elf_Ehdr* hdr);
int elf_count_section(Elf_Ehdr* hdr, Elf_Shdr* shdrs, unsigned int sh_type);
Elf_Shdr* elf_find_section_bytype(Elf_Ehdr* hdr, Elf_Shdr* shdrs, int* start_ndx, unsigned int sh_type);
Elf_Shdr* elf_find_section_byname(Elf_Ehdr* hdr, Elf_Shdr* shdrs, char* shstrs, const char* name);
char* elf_section_addr(char* exec, Elf_Shdr* shdr);
void* elf_load_section(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdr);
char* elf_load_strings(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdrs, Elf_Shdr* tab);
char* elf_load_shstrings(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdrs);
Elf_Shdr* elf_string_header(Elf_Shdr* shdrs, Elf_Shdr* shdr);
char* elf_section_name(Elf_Shdr* shdr, char* shstr);
Elf_Sym* elf_symbol(Elf_Shdr* symhdr, Elf_Sym* symtab, const char* symstr, const char* exec, const char* symname);
const char* elf_dtneed(Elf_Shdr* dynhdr, Elf64_Dyn* dyntab, const char* dynstr, int* dtneed_ndx);
void elf_relocate(Elf_Ehdr* hdr, Elf_Shdr* rela, Elf_Rela* relatab, Elf_Sym* symtab, const char* symstr, int* tls_relas_count, char* exec, void* (*resolve)(const char* symname));
void elf_init(char* exec, Elf_Shdr* dynhdr, Elf64_Dyn* dyntab);
void elf_fini(char* exec, Elf_Shdr* dynhdr, Elf64_Dyn* dyntab);
void elf_print_sections_symbols(void* file /* out txt FILE* */,  char* exec, Elf_Ehdr* hdr, Elf_Shdr* shdrs, char* shstrs);

#ifndef __ASIS__

#define freenull(pp) \
    if (*pp) { \
	free((void*)*pp); \
	*pp = NULL; \
    }

#endif

#endif
