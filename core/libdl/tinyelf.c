#include "libdl.h"
#include <string.h>

Elf_Ehdr* elf_load_hdr(const char* path)
{
   Elf_Ehdr* buf = sys_malloc(sizeof(Elf_Ehdr));
   size_t ret = sys_fread(path, buf, sizeof(Elf_Ehdr), 0);
   if (ret < sizeof(Elf_Ehdr)) {
      sys_free(buf);
      return NULL;
   }
   return buf;
}

Elf_Phdr* elf_load_phdrs(const char* path, Elf_Ehdr* hdr)
{
   if (!hdr) {
      sys_printf(SYS_INFO "elf_load_pheaders: hdr is NULL\n");
      return NULL;
   }
   Elf_Phdr* buf = sys_malloc(sizeof(Elf_Phdr) * hdr->e_phnum);
   size_t ret = sys_fread(path, buf, sizeof(Elf_Phdr) * hdr->e_phnum,
         hdr->e_phoff);
   if (ret < sizeof(Elf_Phdr) * hdr->e_phnum) {
      sys_free(buf);
      return NULL;
   }
   return buf;
}

len_t elf_load_exec(const char* path, Elf_Ehdr* hdr, Elf_Phdr* phdrs,
   char* exec)
{
   len_t size = 0;
   if (!hdr || !phdrs) {
      sys_printf(SYS_INFO "elf_load: hdrs is NULL\n");
      return 0;
   }
   int i;
   for (i = 0; i < hdr->e_phnum; i++) {
      if (phdrs[i].p_type == PT_LOAD || phdrs[i].p_type == PT_TLS) {
         if (!exec) {
            size_t len = phdrs[i].p_memsz;
            size = (size < phdrs[i].p_vaddr + len)? phdrs[i].p_vaddr + len : size;
         } else {
            sys_fread(path, exec + phdrs[i].p_vaddr, phdrs[i].p_filesz, phdrs[i].p_offset);
         }
      }
   }
   return size;
}

Elf_Shdr* elf_load_shdrs(const char* path, Elf_Ehdr* hdr)
{
   if (!hdr) {
      sys_printf(SYS_INFO "elf_load_shdrs: hdrs is NULL\n");
      return NULL;
   }
   Elf_Shdr* buf = sys_malloc(sizeof(Elf_Shdr) * hdr->e_shnum);
   size_t ret = sys_fread(path, buf, sizeof(Elf_Shdr) * hdr->e_shnum,
         hdr->e_shoff);
   if (ret < sizeof(Elf_Shdr) * hdr->e_shnum) {
      sys_free(buf);
      return NULL;
   }
   return buf;;
}

int_t elf_count_table(Elf_Ehdr* hdr, Elf_Shdr* shdrs, unsigned int sh_type)
{
   if (!hdr || !shdrs) {
      sys_printf(SYS_INFO "elf_load_shdrs: hdrs is NULL\n");
      return 0;
   }
   int_t i;
   int_t ret = 0;
   for (i = 0; i < hdr->e_shnum; i++) {
      if (shdrs[i].sh_type == sh_type) {
         ret ++;
      }
   }
   return ret;
}

Elf_Shdr* elf_find_table(Elf_Ehdr* hdr, Elf_Shdr* shdrs, int_t* start_ndx,
   unsigned int sh_type)
{
   if (!hdr || !shdrs) {
      sys_printf(SYS_INFO "elf_load_shdrs: hdrs is NULL\n");
      return NULL;
   }
   int_t i;
   for (i = 0; i < hdr->e_shnum; i++) {
      if (shdrs[i].sh_type == sh_type && i >= *start_ndx) {
         *start_ndx = i;
         return  &shdrs[i];
      }
   }
   return NULL;
}

void* elf_load_table(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdr)
{
   if (!hdr || !shdr) {
      sys_printf(SYS_INFO "elf_load_shdrs: hdrs is NULL\n");
      return NULL;
   }
   void* buf = sys_malloc(shdr->sh_size);
   size_t ret = sys_fread(path, buf, shdr->sh_size, shdr->sh_offset);
   if (ret < shdr->sh_size) {
      sys_free(buf);
      return NULL;
   }
   return buf;;
}

const char* elf_load_strings(const char* path, Elf_Ehdr* hdr, Elf_Shdr* shdrs,
   Elf_Shdr* tab)
{
   if (!hdr || !shdrs || !tab) {
      sys_printf(SYS_INFO "elf_load_strings: hdrs is NULL\n");
      return NULL;
   }
   char* buf = sys_malloc(shdrs[tab->sh_link].sh_size);
   size_t ret = sys_fread(path, buf, shdrs[tab->sh_link].sh_size,
         shdrs[tab->sh_link].sh_offset);
   if (ret < shdrs[tab->sh_link].sh_size) {
      sys_free(buf);
      return NULL;
   }
   return buf;
}

void* elf_symbol(Elf_Shdr* symhdr, Elf_Sym* symtab, const char* symstr,
   const char* exec, const char* symname)
{
   if (!symhdr || !symtab || !symstr) {
      sys_printf(SYS_INFO "elf_symbol: hdrs is NULL\n");
      return NULL;
   }
   addr_t i;
   for (i = 0; i < symhdr->sh_size / symhdr->sh_entsize; i++) {
      if (strcmp(symname, &symstr[symtab[i].st_name]) == 0) {
         if (symtab[i].st_shndx != STN_UNDEF) {
            return (void*)(exec + symtab[i].st_value);
         }
      }
   }
   return NULL;
}

int_t dtneed_ndx = 0;

const char* elf_dtneed(Elf_Shdr* dynhdr, Elf64_Dyn* dyntab, const char* dynstr)
{
   if (!dynhdr || !dyntab) {
      sys_printf(SYS_INFO "elf_dtneed: hdrs is NULL\n");
      return NULL;
   }
   int_t counter = 0;
   addr_t i;
   const char* dlname;
   for (i = 0; i < dynhdr->sh_size / dynhdr->sh_entsize; i++) {
      switch(dyntab[i].d_tag) {
      case DT_NEEDED:
         dlname =  &dynstr[dyntab[i].d_un.d_val];
         if (dtneed_ndx == counter) {
            dtneed_ndx++;
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
