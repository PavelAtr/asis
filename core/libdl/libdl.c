#include <tinysys.h>
#include "libdl.h"
#include <stddef.h>
#include <string.h>
#define __off_t_defined
#include <sys/mman.h>

void elf_free(elf* e)
{
   if (!e) {
      return;
   }
   if (e->hdr) {
      sys_free(e->hdr);
   }
   if (e->phdrs) {
      sys_free(e->phdrs);
   }
   if (e->shdrs) {
      sys_free(e->shdrs);
   }
   int_t ndx;
   for (ndx = 0; e->rela[ndx]; ndx++) {
      if (e->rela[ndx]) {
         if (e->rela[ndx]->relas) {
            sys_free(e->rela[ndx]->relas);
         }
         sys_free(e->rela[ndx]);
      }
   }
   if (e->rela)
      sys_free(e->rela);
   for (ndx = 0; e->sym[ndx]; ndx++) {
      if (e->sym[ndx]) {
         if (e->sym[ndx]->syms) {
            sys_free(e->sym[ndx]->syms);
         }
         if (e->sym[ndx]->symstr) {
            sys_free(e->sym[ndx]->symstr);
         }
         sys_free(e->sym[ndx]);
      }
   }
   if (e->sym)
      sys_free(e->sym);
   if (e->dyntab) {
      sys_free(e->dyntab);
   }
   if (e->dynstr) {
      sys_free((void*)e->dynstr);
   }
   if (e->exec) {
      sys_munmap(e->exec, e->exec_size);
   }
}

dl* dl_find(dl* hndl, const char* path)
{
   dl* s;
   for (s = hndl; s != NULL; s = s->next)
      if (strcmp(s->path, path) == 0) {
         return s;
      }
   return NULL;
}

int dl_load(dl* buf, const char* file)
{
   sys_printf(SYS_INFO "Loading %s ... ", file);
   buf->path = file;
   buf->nlink = 1;
   buf->next = NULL;
   buf->dl_elf = sys_malloc(sizeof(elf));
   buf->dl_elf->hdr = elf_load_hdr(file);
   buf->dl_elf->phdrs = elf_load_phdrs(file, buf->dl_elf->hdr);
   buf->dl_elf->exec_size = elf_load_exec(file, buf->dl_elf->hdr,
         buf->dl_elf->phdrs, NULL);
   buf->dl_elf->exec = sys_mmap(NULL, buf->dl_elf->exec_size,
         PROT_READ | PROT_WRITE | PROT_EXEC,
         MAP_ANONYMOUS|MAP_SHARED, -1, 0);
   memset(buf->dl_elf->exec, 0x0, buf->dl_elf->exec_size);
   elf_load_exec(file, buf->dl_elf->hdr, buf->dl_elf->phdrs, buf->dl_elf->exec);
   buf->dl_elf->shdrs = elf_load_shdrs(file, buf->dl_elf->hdr);
   if (!buf->dl_elf->hdr || !buf->dl_elf->phdrs || !buf->dl_elf->shdrs) {
      goto fail;
   }
   int_t start_ndx = 0;
   int_t i;
   int_t relacnt = elf_count_table(buf->dl_elf->hdr, buf->dl_elf->shdrs, SHT_RELA);
   buf->dl_elf->rela = sys_malloc((relacnt + 1) * sizeof(elfrelas*));
   for (i = 0; i < relacnt; i++) {
      buf->dl_elf->rela[i] = sys_malloc(sizeof(elfrelas));
      buf->dl_elf->rela[i]->head = elf_find_table(buf->dl_elf->hdr,
            buf->dl_elf->shdrs, &start_ndx, SHT_RELA);
      buf->dl_elf->rela[i]->relas = elf_load_table(file, buf->dl_elf->hdr,
            buf->dl_elf->rela[i]->head);
      start_ndx++;
   }
   buf->dl_elf->rela[i] = NULL;
   int_t symcnt = elf_count_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         SHT_SYMTAB);
   int_t dyncnt = elf_count_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         SHT_DYNSYM);
   buf->dl_elf->sym = sys_malloc((symcnt + dyncnt + 1) * sizeof(elfsyms*));
   start_ndx = 0;
   for (i = 0; i < symcnt; i++) {
      buf->dl_elf->sym[i] = sys_malloc(sizeof(elfsyms));
      buf->dl_elf->sym[i]->head = elf_find_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
            &start_ndx, SHT_SYMTAB);
      buf->dl_elf->sym[i]->syms = elf_load_table(file, buf->dl_elf->hdr,
            buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->symstr = elf_load_strings(file, buf->dl_elf->hdr,
            buf->dl_elf->shdrs, buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->dynamic = 0;
      start_ndx++;
   }
   start_ndx = 0;
   for (i = i; i < symcnt + dyncnt; i++) {
      buf->dl_elf->sym[i] = sys_malloc(sizeof(elfsyms));
      buf->dl_elf->sym[i]->head = elf_find_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
            &start_ndx, SHT_DYNSYM);
      buf->dl_elf->sym[i]->syms = elf_load_table(file, buf->dl_elf->hdr,
            buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->symstr = elf_load_strings(file, buf->dl_elf->hdr,
            buf->dl_elf->shdrs, buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->dynamic = 1;
      start_ndx++;
   }
   buf->dl_elf->sym[i] = NULL;
   start_ndx = 0;
   buf->dl_elf->dyns = elf_find_table(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         &start_ndx, SHT_DYNAMIC);
   buf->dl_elf->dyntab = elf_load_table(file, buf->dl_elf->hdr, buf->dl_elf->dyns);
   buf->dl_elf->dynstr = elf_load_strings(file, buf->dl_elf->hdr,
         buf->dl_elf->shdrs, buf->dl_elf->dyns);
   sys_printf(SYS_INFO "OK\n");
   return 0;
fail:
   elf_free(buf->dl_elf);
   return -1;
}

dl* scope;

void* resolve(const char* symname)
{
   return dlsym(scope, symname);
}

void *dlopen(const char* filename, int flags)
{
   dl* prog = sys_malloc(sizeof(dl));
   if (dl_load(prog, filename)) {
      goto fail;
   }
   dl* s = prog;
   while (1) {
      const char* path;
      dtneed_ndx = 0;
      while ((path = elf_dtneed(prog->dl_elf->dyns, prog->dl_elf->dyntab,
                  prog->dl_elf->dynstr)) != NULL) {
         if (dl_find(prog, path) != NULL) {
            continue;
         }
         dl* lib = sys_malloc(sizeof(dl));
         memset(lib, 0x0, sizeof(dl));
         if (dl_load(lib, path)) {
            goto fail;
         }
         s->next = lib;
      }
      s = s->next;
      if (s == NULL) {
         break;
      }
   }
   scope = prog;
   for (s = prog; s != NULL; s = s->next) {
      sys_printf(SYS_INFO "Relocate %s\n", s->path);
      int_t sym_ndx;
      for (sym_ndx = 0; s->dl_elf->sym[sym_ndx]; sym_ndx++)
         if (s->dl_elf->sym[sym_ndx]->dynamic) {
            break;
         }
      int_t rela_ndx;
      for (rela_ndx = 0; s->dl_elf->rela[rela_ndx]; rela_ndx++)
         elf_relocate(s->dl_elf->hdr, s->dl_elf->rela[rela_ndx]->head,
            s->dl_elf->rela[rela_ndx]->relas, s->dl_elf->sym[sym_ndx]->syms,
            s->dl_elf->sym[sym_ndx]->symstr, 0, s->dl_elf->exec, &resolve);
   }
   return prog;
fail:
   dlclose(prog);
   return NULL;
}

void *dlsym(void* hndl, const char* symbol)
{
   dl* s;
   void* sym;
   for (s = hndl; s != NULL; s = s->next) {
      int_t sym_ndx;
      for (sym_ndx = 0; s->dl_elf->sym[sym_ndx]; sym_ndx++) {
         sym = elf_symbol(s->dl_elf->sym[sym_ndx]->head,
               s->dl_elf->sym[sym_ndx]->syms, s->dl_elf->sym[sym_ndx]->symstr,
               s->dl_elf->exec, symbol);
         if (sym) {
            return sym;
         }
      }
   }
   return NULL;
}

int dlclose(void *hndl)
{
   dl* s = hndl;
   if (!s) {
      return 0;
   }
   s->nlink--;
   if (s->nlink) {
      return 0;
   }
   dl* next = s;
   while (next) {
      next = s->next;
      elf_free(s->dl_elf);
      sys_free(s->dl_elf);
      sys_free(s);
      s = next;
   }
   return 0;
}
