#include "libdl.h"
#include "tinyelf.h"
#include <string.h>
#define __off_t_defined
#define __ssize_t_defined
#include <stdio.h>

#ifdef __ASIS__
#include <asis.h>
#else
#include <stdlib.h>
#include <unistd.h>

size_t afread(const char* path, void* ptr, size_t size, size_t off)
{
	FILE* f = fopen(path, "r");
	fseek(f, off, SEEK_SET);
	size_t ret = fread(ptr, 1, size, f);
	fclose(f);
	return ret;
}
#endif

Elf_Ehdr* elf_load_hdr(const char* path)
{
   Elf_Ehdr* buf = malloc(sizeof(Elf_Ehdr));
   size_t ret = afread(path, buf, sizeof(Elf_Ehdr), 0);
   if (ret < sizeof(Elf_Ehdr)) {
      free(buf);
      return NULL;
   }
   return buf;
}

Elf_Phdr* elf_load_phdrs(const char* path, Elf_Ehdr* hdr)
{
   if (!hdr) {
      printf(MARK "%s\n", "elf_load_pheaders: hdr is NULL");
      return NULL;
   }
   Elf_Phdr* buf = malloc(sizeof(Elf_Phdr) * hdr->e_phnum);
   size_t ret = afread(path, buf, sizeof(Elf_Phdr) * hdr->e_phnum,
         hdr->e_phoff);

   if (ret < sizeof(Elf_Phdr) * hdr->e_phnum) {
      free(buf);
      return NULL;
   }
   return buf;
}

size_t elf_load_exec(const char* path, Elf_Ehdr* hdr, Elf_Phdr* phdrs, char* exec, size_t* tls_size, char** tls_initaddr)
{
   size_t size = 0;
   if (!hdr || !phdrs) {
      printf(MARK "%s\n", "elf_load: hdrs is NULL");
      return 0;
   }
   int i;
   for (i = 0; i < hdr->e_phnum; i++) {
      if (phdrs[i].p_type == PT_LOAD) {
         if (!exec) {
            size_t len = phdrs[i].p_memsz;
            size = (size < phdrs[i].p_vaddr + len)? phdrs[i].p_vaddr + len : size;
         } else {
            afread(path, exec + phdrs[i].p_vaddr, phdrs[i].p_filesz, phdrs[i].p_offset);
         }
      }
      if (phdrs[i].p_type == PT_TLS) {
	      *tls_size = phdrs[i].p_memsz;
      	*tls_initaddr = exec + phdrs[i].p_vaddr;
      }
   }
   return size;
}

Elf_Shdr* elf_load_shdrs(const char* path, Elf_Ehdr* hdr)
{
   if (!hdr) {
      printf(MARK "%s\n", "elf_load_shdrs: hdr is NULL");
      return NULL;
   }
   Elf_Shdr* buf = malloc(sizeof(Elf_Shdr) * hdr->e_shnum);
   size_t ret = afread(path, buf, sizeof(Elf_Shdr) * hdr->e_shnum,
         hdr->e_shoff);
   if (ret < sizeof(Elf_Shdr) * hdr->e_shnum) {
      free(buf);
      return NULL;
   }
   return buf;
}

int elf_count_section(Elf_Ehdr* hdr, Elf_Shdr* shdrs, unsigned int sh_type)
{
   if (!hdr || !shdrs) {
      printf(MARK "%s\n", "elf_count_section: hdrs is NULL");
      return 0;
   }
   int i;
   int ret = 0;
   for (i = 0; i < hdr->e_shnum; i++) {
      printf("%s", " "); /* GARBAGE STUB!!!! */
      if (shdrs[i].sh_type == sh_type) {
         ret ++;
      }
   }
   return ret;
}

Elf_Shdr* elf_find_section_bytype(Elf_Ehdr* hdr, Elf_Shdr* shdrs, int* start_ndx,
   unsigned int sh_type)
{
   if (!hdr || !shdrs) {
      printf(MARK "%s\n", "elf_load_shdrs: hdrs is NULL");
      return NULL;
   }
   int i;
   for (i = 0; i < hdr->e_shnum; i++) {
      if (shdrs[i].sh_type == sh_type && i >= *start_ndx) {
         *start_ndx = i;
         return  &shdrs[i];
      }
   }
   return NULL;
}

Elf_Shdr* elf_find_section_byname(Elf_Ehdr* hdr, Elf_Shdr* shdrs, char* shstrs, const char* name)
{
   if (!hdr || !shdrs || ! shstrs) {
      printf(MARK "%s\n", "elf_load_shdrs: hdrs is NULL");
      return NULL;
   }
   int i;
   for (i = 0; i < hdr->e_shnum; i++) {
      if (strcmp(name, &shstrs[shdrs[i].sh_name]) == 0) {
         return  &shdrs[i];
      }
   }
   return NULL;
}

char* elf_section_addr(char* exec, Elf_Shdr* shdr)
{
   if (shdr->sh_addr) {
      return exec + shdr->sh_addr;
   }
   return NULL;
}

void* elf_load_section(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdr)
{
   if (!hdr || !shdr) {
      printf(MARK "%s %p %p\n", "elf_load_section: hdrs is NULL", hdr, shdr);
      return NULL;
   }
   void* buf = malloc(shdr->sh_size);
   size_t ret = afread(path, buf, shdr->sh_size, shdr->sh_offset);
   if (ret < shdr->sh_size) {
      free(buf);
      return NULL;
   }
   return buf;;
}

char* elf_load_strings(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdrs,
   Elf_Shdr* tab)
{
   if (!hdr || !shdrs || !tab) {
      printf(MARK "%s\n", "elf_load_strings: hdrs is NULL");
      return NULL;
   }
   char* buf = malloc(shdrs[tab->sh_link].sh_size);
   size_t ret = afread(path, buf, shdrs[tab->sh_link].sh_size,
         shdrs[tab->sh_link].sh_offset);
   if (ret < shdrs[tab->sh_link].sh_size) {
      free(buf);
      return NULL;
   }
   return buf;
}

char* elf_load_shstrings(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdrs)
{
   if (!hdr || !shdrs) {
      printf(MARK "%s\n", "elf_load_shstr: hdrs is NULL");
      return NULL;
   }
   char* buf = malloc(shdrs[hdr->e_shstrndx].sh_size);
   size_t ret = afread(path, buf, shdrs[hdr->e_shstrndx].sh_size,
         shdrs[hdr->e_shstrndx].sh_offset);
   if (ret < shdrs[hdr->e_shstrndx].sh_size) {
      free(buf);
      return NULL;
   }
   return buf;
}

Elf_Shdr* elf_string_header(Elf_Shdr* shdrs, Elf_Shdr* shdr)
{
   if (!shdr || !shdr) {
      printf(MARK "%s\n", "elf_string_header: hdrs is NULL");
      return NULL;
   }
   return &shdrs[shdr->sh_link];
}

char* elf_section_name(Elf_Shdr* shdr, char* shstr)
{
   if (!shdr || !shstr) {
      printf(MARK "%s\n", "elf_section_name: hdrs is NULL");
      return NULL;
   }
   return &shstr[shdr->sh_name];
}

Elf_Sym* elf_symbol(Elf_Shdr* symhdr, Elf_Sym* symtab, const char* symstr,
   const char* exec, const char* symname)
{
   if (!symhdr || !symtab || !symstr) {
      printf(MARK "%s\n", "elf_symbol: hdrs is NULL");
      return NULL;
   }
   addr_t i;
   for (i = 0; i < symhdr->sh_size / symhdr->sh_entsize; i++) {
      if (strcmp(symname, &symstr[symtab[i].st_name]) == 0) {
         if (symtab[i].st_shndx != SHN_UNDEF) {
            return &symtab[i];
         }
      }
   }
   return NULL;
}

const char* elf_dtneed(Elf_Shdr* dynhdr, Elf64_Dyn* dyntab, const char* dynstr, int* dtneed_ndx)
{
   if (!dynhdr || !dyntab) {
      printf(MARK "%s\n", "elf_dtneed: hdrs is NULL");
      return NULL;
   }
   int counter = 0;
   int i;
   const char* dlname;
   for (i = 0; i < (int)(dynhdr->sh_size / dynhdr->sh_entsize); i++) {
      switch(dyntab[i].d_tag) {
      case DT_NEEDED:
         dlname =  &dynstr[dyntab[i].d_un.d_val];
         if (*dtneed_ndx == counter) {
            *dtneed_ndx = counter + 1;
            return dlname;
         }
         counter++;
         break;
      default :
         break;
      }
   }
   return NULL;
}

void elf_init(char* exec, Elf_Shdr* dynhdr, Elf64_Dyn* dyntab)
{
   if (!dynhdr || !dyntab) {
      printf(MARK "%s\n", "elf_init: hdrs is NULL");
      return;
   }
   int i;
   for (i = 0; i < (int)(dynhdr->sh_size / dynhdr->sh_entsize); i++) {
      switch(dyntab[i].d_tag) {
      case DT_INIT:
         void (*func)() = (void*)(exec + dyntab[i].d_un.d_ptr);
         printf(MARK "Found init %p\n", func);
         func();
         break;
      default :
         break;
      }
   }

   long_t* dt_init_array = NULL;
   int dt_init_arraysz = 0;
   for (i = 0; i < (int)(dynhdr->sh_size / dynhdr->sh_entsize); i++) {
      switch(dyntab[i].d_tag) {
      case DT_INIT_ARRAY:
         dt_init_array = (long_t*)(exec + dyntab[i].d_un.d_ptr);
         break;
      case DT_INIT_ARRAYSZ:
          dt_init_arraysz = dyntab[i].d_un.d_val;
          break;
      default :
         break;
      }
   }
   for (i = 0; i < (int)(dt_init_arraysz / sizeof(long_t)); i++) {
      void (*func)() = (void*)(dt_init_array[i]);
      func();
   }
 }

void elf_fini(char* exec, Elf_Shdr* dynhdr, Elf64_Dyn* dyntab)
{
   if (!dynhdr || !dyntab) {
      printf(MARK "%s\n", "elf_init: hdrs is NULL");
      return;
   }
   int i;
   for (i = 0; i < (int)(dynhdr->sh_size / dynhdr->sh_entsize); i++) {
      switch(dyntab[i].d_tag) {
      case DT_FINI:
         void (*func)() = (void*)(exec + dyntab[i].d_un.d_ptr);
         func();
         break;
      default :
         break;
      }
   }
   long_t* dt_fini_array = NULL;
   int dt_fini_arraysz = 0;
   for (i = 0; i < (int)(dynhdr->sh_size / dynhdr->sh_entsize); i++) {
      switch(dyntab[i].d_tag) {
      case DT_FINI_ARRAY:
         dt_fini_array = (long_t*)(exec + dyntab[i].d_un.d_ptr);
         break;
      case DT_FINI_ARRAYSZ:
          dt_fini_arraysz = dyntab[i].d_un.d_val;
          break;
      default :
         break;
      }
   }
   for (i = 0; i < (int)(dt_fini_arraysz / sizeof(long_t)); i++) {
      void (*func)() = (void*)(dt_fini_array[i]);
      func();
   }
 }

void elf_print_sections_symbols(void* file, char* exec, Elf_Ehdr* hdr, Elf_Shdr* shdrs, char* shstrs)
{
   int i;
   if (!file || !exec || !hdr || !shdrs || !shstrs) {
      printf(MARK "%s\n", "elf_print_sections_symbols: hdrs is NULL");
      return;
   }
   for (i = 0; i < hdr->e_shnum; i++) {
      if (shdrs[i].sh_addr)
      {
         char* section_addr = exec + shdrs[i].sh_addr;
         char* section_name = &shstrs[shdrs[i].sh_name];
         if (strcmp(section_name, ".text") != 0) {
            continue; // Skip common sections
         }
         fprintf(file, " -s %s %p", section_name, section_addr);
      }
   } 
}
