#include "../tinyelf.h"
#include <tinysys.h>
#include <string.h>

#define R_IRELATIVE R_X86_64_IRELATIVE
#define R_RELATIVE R_X86_64_RELATIVE
#define R_COPY R_X86_64_COPY
#define R_TPOFF64 R_X86_64_TPOFF64
#define R_64 R_X86_64_64
#define R_GLOB_DAT R_X86_64_GLOB_DAT
#define R_JUMP_SLOT R_X86_64_JUMP_SLOT

void elf_relocate(Elf_Ehdr* hdr, Elf_Shdr* rela, Elf_Rela* relatab, Elf_Sym* symtab, const char* symstr, Elf_Xword tls_offset, char* exec, void* (*resolve)(const char* symname))
{
  if (!hdr || !rela || !relatab || !symtab || ! symstr) {
    sys_printf(SYS_INFO "elf_relocate: hdrs is NULL\n");
    return ;
  }
  addr_t j;
  for(j = 0; j < rela->sh_size / rela->sh_entsize; j ++) {
    void* symaddr;
    const char* symname = &symstr[symtab[ELF_R_SYM(relatab[j].r_info)].st_name];
    if (resolve)
      symaddr = resolve(symname);
    switch (ELF_R_TYPE(relatab[j].r_info)) {
    case R_IRELATIVE:
      *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword)((long_t)exec + relatab[j].r_addend);
      break;
    case R_RELATIVE:
      *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword)((long_t)exec + relatab[j].r_addend);
      break;
    case R_COPY:
      if (!symaddr) {
        sys_printf(SYS_INFO "elf_relocate: %s R_COPY NOT FOUND\n", symname);
        break;
      }
      memcpy(exec + relatab[j].r_offset,	symaddr, symtab[ELF_R_SYM(relatab[j].r_info)].st_size);
      break;
    case R_TPOFF64:
      *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword)(symtab[ELF_R_SYM(relatab[j].r_info)].st_value + relatab[j].r_addend + tls_offset + exec);
      break;
    case R_64:
      if (!symaddr) {
        sys_printf(SYS_INFO "elf_relocate: %s R_64 NOT FOUND\n", symname);
        break;
      }
      *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword)(symaddr + relatab[j].r_addend);
      break;
    case R_GLOB_DAT:
      if (!symaddr) {
        sys_printf(SYS_INFO "elf_relocate: %s R_GLOB_DAT NOT FOUND\n", symname);
        break;
      }
      *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword) symaddr;
      break;
    case R_JUMP_SLOT:
      if (!symaddr) {
        sys_printf(SYS_INFO "elf_relocate: %s R_JUMP_SLOT NOT FOUND\n", symname);
        break;
      }
      *(Elf_Xword*)(exec + relatab[j].r_offset) = (Elf_Xword) symaddr;
      break;
    default:
      sys_printf(SYS_INFO "UNREALIZED RELA %s %ld \n", symname, ELF_R_TYPE(relatab[j].r_info));
      break;
    }
  }
}

