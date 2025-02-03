#include <tinysys.h>
#include "libdl.h"
#include <stddef.h>
#include <string.h>
#define __off_t_defined
#include <sys/mman.h>
#include <sys/stat.h>

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
      sys_free(e->dynstr);
   }
   if (e->exec) {
      sys_munmap(e->exec, e->exec_size);
   }
}

dl* dl_find(dl* hndl, const char* path)
{
   dl* s;
   sys_printf(SYS_DEBUG "SEARCHING %s ", path);
   for (s = hndl; s != NULL; s = s->next) {
      if (strcmp(s->path, path) == 0) {
		  sys_printf("ALREDY\n");
         return s;
      }
   }
   sys_printf("NEEDLOAD\n");
   return NULL;
}

int dl_load(dl* buf, const char* file)
{
   sys_printf(SYS_INFO "Loading %s ... ", file);
   buf->path = file;
   buf->next = NULL;
   buf->dl_elf = calloc(1, sizeof(elf));
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
   
   buf->dl_elf->rela = malloc((relacnt + 1) * sizeof(elfrelas*));
   for (i = 0; i < relacnt; i++) {
      buf->dl_elf->rela[i] = malloc(sizeof(elfrelas));
      buf->dl_elf->rela[i]->head = elf_find_table(buf->dl_elf->hdr,
            buf->dl_elf->shdrs, &start_ndx, SHT_RELA);
      buf->dl_elf->rela[i]->relas = elf_load_table(file, buf->dl_elf->hdr,
            buf->dl_elf->rela[i]->head);
      start_ndx++;
   }
   buf->dl_elf->rela[i] = NULL;

   buf->dl_elf->tlsrela = sys_malloc((relacnt + 1) * sizeof(tlsrelas*));   
   for (i = 0; i < relacnt; i++) {
      buf->dl_elf->tlsrela[i] = calloc(1, sizeof(elfrelas));
   }
   buf->dl_elf->tlsrela[i] = NULL;
   
   
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
   buf->nlink = 1;      
   sys_printf("OK\n");
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

char* ldpath(const char* path, const char* file)
{
   short found = 0;
   size_t pathlen = 0;
   char* system_path = NULL;
   if (path) {
      system_path = strdup(path);
      pathlen = strlen(system_path);
   }
   char* rezult = sys_malloc(pathlen + strlen(file) + 2);
   if (file[0] == '/' || !system_path) {
      strcpy(rezult, file);
      goto end;
   }
   char* dir = strtok(system_path, ":");
   while (dir != NULL) {
      strcpy(rezult, dir);
      strcpy(rezult + strlen(dir), file);
      dir =strtok(NULL, ":");
      struct stat st;
      if (sys_stat(rezult, &st) != -1) {
         found = 1;
         break;
      }
   }
end:
   if (system_path) {
      sys_free(system_path);
   }
   if (found) {
      return rezult;
   } else {
      return NULL;
   }
}


void *dlopen(const char* filename, int flags)
{
   dl* prog = sys_malloc(sizeof(dl));
   memset(prog, 0x0, sizeof(dl));
   if (dl_load(prog, filename)) {
      goto fail;
   }
   dl* s = prog;
   while (1) {
      const char* file;
      dtneed_ndx = 0;
      while (file = elf_dtneed(prog->dl_elf->dyns, prog->dl_elf->dyntab,
                  prog->dl_elf->dynstr)) {
		 char* path = ldpath(LD_PATH, file);
		 if (!path) {
            sys_printf(SYS_ERROR "%s not found in %s\n", file, LD_PATH);
		    goto fail;
	     }	 
		 sys_printf(SYS_DEBUG "NEEDED %s\n", file);			  
         if (dl_find(prog, path)) {
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
      int rela_ndx;
      for (rela_ndx = 0; s->dl_elf->rela[rela_ndx]; rela_ndx++) {
		 int tls_relas_count = 0; 
         elf_relocate(s->dl_elf->hdr, s->dl_elf->rela[rela_ndx]->head,
            s->dl_elf->rela[rela_ndx]->relas, s->dl_elf->sym[sym_ndx]->syms,
            s->dl_elf->sym[sym_ndx]->symstr, &tls_relas_count, s->dl_elf->exec, &resolve);
		 s->dl_elf->tlsrela[rela_ndx]->count = tls_relas_count;
         s->dl_elf->tlsrela[rela_ndx]->relas = elf_copy_tls_rela(s->dl_elf->rela[rela_ndx]->head,
            s->dl_elf->rela[rela_ndx]->relas, tls_relas_count);  
      }     
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
   dl* next = s;
   while (next) {
      next = s->next;
      s->nlink--;
      if (s->nlink <= 0) {
	     elf_free(s->dl_elf);
         sys_free(s->dl_elf);
         sys_free(s);
      }
      s = next;
   }
   return 0;
}

void dltls(void* handle, unsigned long module_id)
{
   dl* s;
   for (s = handle; s != NULL; s = s->next) {
      int rela_ndx;
      for (rela_ndx = 0; s->dl_elf->rela[rela_ndx]; rela_ndx++) {
         if (s->dl_elf->tlsrela[rela_ndx]->relas) {
			 int i;
			 for (i = 0; i < s->dl_elf->tlsrela[rela_ndx]->count; i++)
			 {
				 *(Elf_Xword*)(s->dl_elf->exec + s->dl_elf->tlsrela[rela_ndx]->relas[i].r_offset) = module_id;
     			 sys_printf("FOUND %d TLS rela %p=%p\n", s->dl_elf->tlsrela[rela_ndx]->count, &s->dl_elf->tlsrela[rela_ndx]->relas[i], s->dl_elf->tlsrela[rela_ndx]->relas[i].r_offset);
			 }
/*		 s->dl_elf->tlsrela[rela_ndx]->count = tls_relas_count;
         s->dl_elf->tlsrela[rela_ndx]->relas = elf_copy_tls_rela(s->dl_elf->rela[rela_ndx]->head,
            s->dl_elf->rela[rela_ndx]->relas, tls_relas_count);  */
         }

      }
	   s->dl_elf->tls_index = module_id;
   }
}
