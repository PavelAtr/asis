#include "../tinyelf.h"
#include <string.h>
#define __off_t_defined
#define __ssize_t_defined

#ifdef __ASIS__
#include <asis.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif

#define R_IRELATIVE R_X86_64_IRELATIVE
#define R_RELATIVE R_X86_64_RELATIVE
#define R_COPY R_X86_64_COPY
#define R_TPOFF64 R_X86_64_TPOFF64
#define R_64 R_X86_64_64
#define R_GLOB_DAT R_X86_64_GLOB_DAT
#define R_JUMP_SLOT R_X86_64_JUMP_SLOT
#define R_DTPMOD64 R_X86_64_DTPMOD64
#define R_DTPOFF64 R_X86_64_DTPOFF64
#define R_TPOFF64 R_X86_64_TPOFF64

void elf_relocate(Elf_Ehdr* hdr, Elf_Shdr* rela, Elf_Rela* relatab,
   Elf_Sym* symtab, const char* symstr, int* tls_relas_count, char* exec,
   void* (*resolve)(const char* symname))
{
   if (!hdr || !rela || !relatab || !symtab || ! symstr) {
      printf(MARK "%s  %p %p %p %p %p\n", "elf_relocate: hdrs is NULL",
         hdr, rela, relatab, symtab, symstr);
      return ;
   }
   int j;
   for(j = 0; j < (int)(rela->sh_size / rela->sh_entsize); j ++) {
      void* symaddr;
      const char* symname = &symstr[symtab[ELF_R_SYM(relatab[j].r_info)].st_name];
      if (resolve) {
         symaddr = resolve(symname);
      }
      switch (ELF_R_TYPE(relatab[j].r_info)) {
      case R_IRELATIVE:
         *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword)((
                  long_t)exec + relatab[j].r_addend);
         break;
      case R_RELATIVE:
         *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword)((
                  long_t)exec + relatab[j].r_addend);
         break;
      case R_COPY:
         if (!symaddr) {
            printf(MARK "elf_relocate: %s R_COPY NOT FOUND\n", symname);
            break;
         }
         memcpy(exec + relatab[j].r_offset,	symaddr,
            symtab[ELF_R_SYM(relatab[j].r_info)].st_size);
         break;
      case R_64:
         if (!symaddr) {
            printf(MARK "elf_relocate: %s R_64 NOT FOUND\n", symname);
            break;
         }
         *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword)(
               symaddr + relatab[j].r_addend);
         break;
      case R_GLOB_DAT:
         if (!symaddr) {
            printf(MARK "elf_relocate: %s R_GLOB_DAT NOT FOUND\n", symname);
            break;
         }
         *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword) symaddr;
         break;
      case R_JUMP_SLOT:
         if (!symaddr) {
            printf(MARK "elf_relocate: %s R_JUMP_SLOT NOT FOUND\n", symname);
            break;
         }
         *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword) symaddr;
         break;
      case R_DTPMOD64:
         break;
      case R_DTPOFF64:
         break;
      default:
         printf(MARK "UNREALIZED RELA %s %ld \n", symname,
            ELF_R_TYPE(relatab[j].r_info));
         break;
      }
   }
}
