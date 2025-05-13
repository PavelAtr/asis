#include "libdl.h"
#include "dlfcn.h"
#include <stddef.h>
#include <string.h>
#define __off_t_defined
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>

void elf_free(elf* e)
{
   if (!e) {
      return;
   }
   if (e->hdr) {
      free(e->hdr);
   }
   if (e->phdrs) {
      free(e->phdrs);
   }
   if (e->shdrs) {
      free(e->shdrs);
   }
   if (e->shstr) {
      free(e->shstr);
   }
   int ndx;
   for (ndx = 0; e->rela[ndx]; ndx++) {
      if (e->rela[ndx]) {
         if (e->rela[ndx]->relas) {
            free(e->rela[ndx]->relas);
         }
         free(e->rela[ndx]);
      }
   }
   for (ndx = 0; e->rela[ndx]; ndx++) {
      if (e->tlsrela[ndx]) {
         if (e->tlsrela[ndx]->relas) {
            free(e->tlsrela[ndx]->relas);
         }
         free(e->tlsrela[ndx]);
      }
   }
   if (e->rela)
      free(e->rela);
   for (ndx = 0; e->sym[ndx]; ndx++) {
      if (e->sym[ndx]) {
         if (e->sym[ndx]->syms) {
            free(e->sym[ndx]->syms);
         }
         if (e->sym[ndx]->symstr) {
            free(e->sym[ndx]->symstr);
         }
         free(e->sym[ndx]);
      }
   }
   if (e->sym)
      free(e->sym);
   if (e->dyntab) {
      free(e->dyntab);
   }
   if (e->dynstr) {
      free(e->dynstr);
   }
   if (e->exec) {
      munmap(e->exec, e->exec_size);
   }
}

int dl_load(dl* buf, const char* file)
{
   printf(MARK "Loading %s ... ", file);
   buf->path = strdup(file);
   buf->dl_elf = calloc(1, sizeof(elf));
   buf->dl_elf->hdr = elf_load_hdr(file);
   buf->dl_elf->phdrs = elf_load_phdrs(file, buf->dl_elf->hdr);
   buf->dl_elf->exec_size = elf_load_exec(file, buf->dl_elf->hdr,
         buf->dl_elf->phdrs, NULL, &buf->dl_elf->tls_size);
   buf->dl_elf->exec = mmap(NULL, buf->dl_elf->exec_size,
         PROT_READ | PROT_WRITE | PROT_EXEC,
         MAP_ANONYMOUS|MAP_SHARED, -1, 0);
   memset(buf->dl_elf->exec, 0x0, buf->dl_elf->exec_size);
   elf_load_exec(file, buf->dl_elf->hdr, buf->dl_elf->phdrs, buf->dl_elf->exec, &buf->dl_elf->tls_size);
   buf->dl_elf->shdrs = elf_load_shdrs(file, buf->dl_elf->hdr);
   if (!buf->dl_elf->hdr || !buf->dl_elf->phdrs || !buf->dl_elf->shdrs) {
      goto fail;
   }
   buf->dl_elf->shstr = elf_load_shstrings(file, buf->dl_elf->hdr, buf->dl_elf->shdrs);
   int start_ndx = 0;
   int i;
   int relacnt = elf_count_section(buf->dl_elf->hdr, buf->dl_elf->shdrs, SHT_RELA);
   
   buf->dl_elf->rela = malloc((relacnt + 1) * sizeof(elfrelas*));
   for (i = 0; i < relacnt; i++) {
      buf->dl_elf->rela[i] = malloc(sizeof(elfrelas));
      buf->dl_elf->rela[i]->head = elf_find_section_bytype(buf->dl_elf->hdr,
            buf->dl_elf->shdrs, &start_ndx, SHT_RELA);
      buf->dl_elf->rela[i]->relas = elf_load_section(file, buf->dl_elf->hdr,
            buf->dl_elf->rela[i]->head);
      start_ndx++;
   }
   buf->dl_elf->rela[i] = NULL;

   buf->dl_elf->tlsrela = malloc((relacnt + 1) * sizeof(tlsrelas*));   
   for (i = 0; i < relacnt; i++) {
      buf->dl_elf->tlsrela[i] = calloc(1, sizeof(elfrelas));
   }
   buf->dl_elf->tlsrela[i] = NULL;

   start_ndx = 0;
   buf->dl_elf->dynsym_hdr = elf_find_section_bytype(buf->dl_elf->hdr, buf->dl_elf->shdrs,
      &start_ndx, SHT_DYNSYM);
   buf->dl_elf->dynsym_tab = (Elf_Sym*)(buf->dl_elf->exec + buf->dl_elf->dynsym_hdr->sh_offset);
   buf->dl_elf->dynsym_str = buf->dl_elf->exec + buf->dl_elf->shdrs[buf->dl_elf->dynsym_hdr->sh_link].sh_offset;
  
   
/*   int symcnt = elf_count_section(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         SHT_SYMTAB);*/
   int symcnt = 0;      
/*   int dyncnt = elf_count_section(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         SHT_DYNSYM);*/
   int dyncnt = 0;      
   buf->dl_elf->sym = malloc((symcnt + dyncnt + 1) * sizeof(elfsyms*));
   i = 0;
/*   start_ndx = 0;
   for (i = 0; i < symcnt; i++) {
      buf->dl_elf->sym[i] = malloc(sizeof(elfsyms));
      buf->dl_elf->sym[i]->head = elf_find_section_bytype(buf->dl_elf->hdr, buf->dl_elf->shdrs,
            &start_ndx, SHT_SYMTAB);
      buf->dl_elf->sym[i]->syms = elf_load_section(file, buf->dl_elf->hdr,
            buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->symstr = elf_load_strings(file, buf->dl_elf->hdr,
            buf->dl_elf->shdrs, buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->strhead = elf_string_header(buf->dl_elf->shdrs, buf->dl_elf->sym[i]->head);
      printf("\nstring section name=%s\n", elf_section_name( buf->dl_elf->sym[i]->strhead, buf->dl_elf->shstr)); // GARBAGE         
      buf->dl_elf->sym[i]->dynamic = 0;
      printf("\nsymbol section name=%s\n", elf_section_name( buf->dl_elf->sym[i]->head, buf->dl_elf->shstr)); // GARBAGE
      start_ndx++;
   }
   start_ndx = 0;
   for (i = i; i < symcnt + dyncnt; i++) {
      buf->dl_elf->sym[i] = malloc(sizeof(elfsyms));
      buf->dl_elf->sym[i]->head = elf_find_section_bytype(buf->dl_elf->hdr, buf->dl_elf->shdrs,
            &start_ndx, SHT_DYNSYM);
      buf->dl_elf->sym[i]->syms = elf_load_section(file, buf->dl_elf->hdr,
            buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->symstr = elf_load_strings(file, buf->dl_elf->hdr,
            buf->dl_elf->shdrs, buf->dl_elf->sym[i]->head);
      buf->dl_elf->sym[i]->strhead = elf_string_header(buf->dl_elf->shdrs, buf->dl_elf->sym[i]->head);
      printf("\nstring section name=%s\n", elf_section_name( buf->dl_elf->sym[i]->strhead, buf->dl_elf->shstr)); // GARBAGE         
      buf->dl_elf->sym[i]->dynamic = 1;
      printf("\nsymbol section name=%s\n", elf_section_name( buf->dl_elf->sym[i]->head, buf->dl_elf->shstr)); // GARBAGE         
      start_ndx++;
   }*/
   buf->dl_elf->sym[i] = NULL;
   start_ndx = 0;
   buf->dl_elf->dyns = elf_find_section_bytype(buf->dl_elf->hdr, buf->dl_elf->shdrs,
         &start_ndx, SHT_DYNAMIC);
   buf->dl_elf->dyntab = elf_load_section(file, buf->dl_elf->hdr,
      buf->dl_elf->dyns);
   buf->dl_elf->dynstr = elf_load_strings(file, buf->dl_elf->hdr,
         buf->dl_elf->shdrs, buf->dl_elf->dyns);
   #ifdef USE_SYMBOLFILE
   buf->dl_elf->debug_aranges_head = elf_find_section_byname(
      buf->dl_elf->hdr, buf->dl_elf->shdrs, buf->dl_elf->shstr, ".debug_aranges");
   buf->dl_elf->debug_aranges_addr = elf_load_section(file, buf->dl_elf->hdr,
      buf->dl_elf->debug_aranges_head);
   buf->dl_elf->debug_info_head = elf_find_section_byname(
      buf->dl_elf->hdr, buf->dl_elf->shdrs, buf->dl_elf->shstr, ".debug_info");
   buf->dl_elf->debug_info_addr = elf_load_section(file, buf->dl_elf->hdr,
      buf->dl_elf->debug_info_head);
   buf->dl_elf->debug_abbrev_head = elf_find_section_byname(
      buf->dl_elf->hdr, buf->dl_elf->shdrs, buf->dl_elf->shstr, ".debug_abbrev");
   buf->dl_elf->debug_abbrev_addr = elf_load_section(file, buf->dl_elf->hdr,
      buf->dl_elf->debug_abbrev_head);
   buf->dl_elf->debug_line_head = elf_find_section_byname(
      buf->dl_elf->hdr, buf->dl_elf->shdrs, buf->dl_elf->shstr, ".debug_line");
   buf->dl_elf->debug_line_addr = elf_load_section(file, buf->dl_elf->hdr,
      buf->dl_elf->debug_line_head);
   buf->dl_elf->debug_str_head = elf_find_section_byname(
      buf->dl_elf->hdr, buf->dl_elf->shdrs, buf->dl_elf->shstr, ".debug_str");
   buf->dl_elf->debug_str_addr = elf_load_section(file, buf->dl_elf->hdr,
      buf->dl_elf->debug_str_head);
   buf->dl_elf->debug_line_str_head = elf_find_section_byname(
      buf->dl_elf->hdr, buf->dl_elf->shdrs, buf->dl_elf->shstr, ".debug_line_str");
   buf->dl_elf->debug_line_str_addr = elf_load_section(file, buf->dl_elf->hdr,
      buf->dl_elf->debug_line_str_head);
   buf->dl_elf->debug_rnglists_head = elf_find_section_byname(
      buf->dl_elf->hdr, buf->dl_elf->shdrs, buf->dl_elf->shstr, ".debug_rnglists");
   buf->dl_elf->debug_rnglists_addr = elf_load_section(file, buf->dl_elf->hdr,
      buf->dl_elf->debug_rnglists_head);
   #endif
   printf("%s\n", "OK");
   return 0;
fail:
   elf_free(buf->dl_elf);
   return -1;
}

dlhandle* relascope;
dlhandle* selfscope;
dlhandle* globalscope = NULL;

void* resolve(const char* symname)
{
   void* addr = dlsym(selfscope, symname);
   if (addr) {
	  return addr;
   }
   return dlsym(relascope, symname);
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
   char* rezult = malloc(pathlen + strlen(file) + 2);
   if (file[0] == '/' || !system_path) {
      strcpy(rezult, file);
      goto end;
   }
   char* dir = strtok(system_path, ":");
   while (dir != NULL) {
      strcpy(rezult, dir);
      strcpy(rezult + strlen(dir), "/");
      strcpy(rezult + strlen(dir) + 1, file);
      dir =strtok(NULL, ":");
      struct stat st;
      if (stat(rezult, &st) != -1) {
         found = 1;
         break;
      }
   }
end:
   if (system_path) {
      free(system_path);
   }
   if (found) {
      return rezult;
   } else {
      return NULL;
   }
}

void *dlopen(const char* filename, int flags)
{
   dl* prog = calloc(1, sizeof(dl));

   if (dl_load(prog, filename) == -1) {
      goto fail;
   }
   dlhandle* handle = (dlhandle*)namedlist_add(NULL, prog,  prog->path);
   #ifdef USE_SYMBOLFILE
   FILE* symfile = fopen("dl.txt", "a");
   fprintf(symfile, "add-symbol-file %s %p ", prog->path, prog->dl_elf->exec);
   int sym_ndx;
   for (sym_ndx = 0; prog->dl_elf->sym[sym_ndx]; sym_ndx++) {
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->sym[sym_ndx]->head, prog->dl_elf->shstr),
         prog->dl_elf->sym[sym_ndx]->syms);
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->sym[sym_ndx]->strhead, prog->dl_elf->shstr),
         prog->dl_elf->sym[sym_ndx]->symstr);
   }
   if (prog->dl_elf->debug_aranges_head) {
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->debug_aranges_head, prog->dl_elf->shstr),
         prog->dl_elf->debug_aranges_addr);
   }
   if (prog->dl_elf->debug_info_head) {
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->debug_info_head, prog->dl_elf->shstr),
         prog->dl_elf->debug_info_addr);
   }
   if (prog->dl_elf->debug_abbrev_head) {
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->debug_abbrev_head, prog->dl_elf->shstr),
         prog->dl_elf->debug_abbrev_addr);
   }
   if (prog->dl_elf->debug_line_head) {
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->debug_line_head, prog->dl_elf->shstr),
         prog->dl_elf->debug_line_addr);
   }
   if (prog->dl_elf->debug_str_head) {
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->debug_str_head, prog->dl_elf->shstr),
         prog->dl_elf->debug_str_addr);
   }
   if (prog->dl_elf->debug_line_str_head) {
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->debug_line_str_head, prog->dl_elf->shstr),
         prog->dl_elf->debug_line_str_addr);
   }
   if (prog->dl_elf->debug_rnglists_head) {
      fprintf(symfile, "-s %s %p ", elf_section_name(
         prog->dl_elf->debug_rnglists_head, prog->dl_elf->shstr),
         prog->dl_elf->debug_rnglists_addr);
   }
   fprintf(symfile, "\n");
   fclose(symfile);
   #endif
   dlhandle* j;
   for (j = handle; j; j = j->next) {
      dl* s = j->obj;
      const char* file;
      int dtneed_ndx = 0;
      printf(MARK "Resolving dependencies of %s\n", s->path);
      while (file = elf_dtneed(s->dl_elf->dyns, s->dl_elf->dyntab,
                  s->dl_elf->dynstr, &dtneed_ndx)) {
		 char* path = ldpath(ld_library_path, file);
		 if (!path) {
            printf(MARK "%s not found in %s\n", file, ld_library_path);
		    goto fail;
	     }	 
         if (namedlist_get((namedlist*)handle, path)) {
    	    printf(MARK "NEEDED %s ALREDY\n", path);			  
            continue;
         }
         dl* lib;
         if ((lib = namedlist_get((namedlist*)globalscope, path)))
         {
			printf(MARK "InCache %s\n", path);			  
	     } else {
            lib = calloc(1, sizeof(dl));
            if (dl_load(lib, path) == -1) {
                goto fail;
            }   
         }
         handle = (dlhandle*)namedlist_add((namedlist*)handle, lib, lib->path);
         lib->nlink++;
         #ifdef USE_SYMBOLFILE
            FILE* symfile = fopen("dl.txt", "a");
            fprintf(symfile, "add-symbol-file %s %p ", lib->path, lib->dl_elf->exec);
            int sym_ndx;
            for (sym_ndx = 0; lib->dl_elf->sym[sym_ndx]; sym_ndx++) {
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  lib->dl_elf->sym[sym_ndx]->head, lib->dl_elf->shstr),
                  lib->dl_elf->sym[sym_ndx]->syms);
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  lib->dl_elf->sym[sym_ndx]->strhead, lib->dl_elf->shstr),
                  lib->dl_elf->sym[sym_ndx]->symstr);
            }
            if (prog->dl_elf->debug_aranges_head) {
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  prog->dl_elf->debug_aranges_head, prog->dl_elf->shstr),
                  prog->dl_elf->debug_aranges_addr);
            }
            if (prog->dl_elf->debug_info_head) {
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  prog->dl_elf->debug_info_head, prog->dl_elf->shstr),
                  prog->dl_elf->debug_info_addr);
            }
            if (prog->dl_elf->debug_abbrev_head) {
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  prog->dl_elf->debug_abbrev_head, prog->dl_elf->shstr),
                  prog->dl_elf->debug_abbrev_addr);
            }
            if (prog->dl_elf->debug_line_head) {
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  prog->dl_elf->debug_line_head, prog->dl_elf->shstr),
                  prog->dl_elf->debug_line_addr);
            }
            if (prog->dl_elf->debug_str_head) {
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  prog->dl_elf->debug_str_head, prog->dl_elf->shstr),
                  prog->dl_elf->debug_str_addr);
            }
            if (prog->dl_elf->debug_line_str_head) {
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  prog->dl_elf->debug_line_str_head, prog->dl_elf->shstr),
                  prog->dl_elf->debug_line_str_addr);
            }
            if (prog->dl_elf->debug_rnglists_head) {
               fprintf(symfile, "-s %s %p ", elf_section_name(
                  prog->dl_elf->debug_rnglists_head, prog->dl_elf->shstr),
                  prog->dl_elf->debug_rnglists_addr);
            }
            fprintf(symfile, "\n");
            fclose(symfile);
         #endif
      }
   }
   relascope = handle; 
   for (j = handle; j; j = j->next) {
	  dl* s  = j->obj;
	  if (s->status & DL_RELOCATED) {
		  continue;
	  }
      printf(MARK "Relocate %s\n", s->path);
      selfscope = j;
      int rela_ndx;
      for (rela_ndx = 0; s->dl_elf->rela[rela_ndx]; rela_ndx++) {
		 int tls_relas_count = 0; 
       elf_relocate(s->dl_elf->hdr, s->dl_elf->rela[rela_ndx]->head,
         s->dl_elf->rela[rela_ndx]->relas, s->dl_elf->dynsym_tab,
         s->dl_elf->dynsym_str, &tls_relas_count, s->dl_elf->exec, &resolve);
		 s->dl_elf->tlsrela[rela_ndx]->count = tls_relas_count;
         s->dl_elf->tlsrela[rela_ndx]->relas = elf_copy_tls_rela(s->dl_elf->rela[rela_ndx]->head,
         s->dl_elf->rela[rela_ndx]->relas, tls_relas_count);
      }
      s->status |= DL_RELOCATED;
   }
   for (j = handle; j != NULL; j = j->next) {
	  dl* s  = j->obj;
	  if (s->status & DL_INITED) {
		  continue;
	  }
      printf(MARK "Init %s\n", s->path);
      elf_init(s->dl_elf->exec, s->dl_elf->dyns, s->dl_elf->dyntab);
      void* (*allocate_tls)(size_t) = dlsym(j, "allocate_tls");
      if (allocate_tls) {
		  allocate_tls(s->dl_elf->tls_size);
	  }
      s->status |= DL_INITED;
   }
   for (j = handle->next; j != NULL; j = j->next) {
	  dl* s  = j->obj;
	  if (namedlist_get((namedlist*)globalscope, s->path)) {
		  continue;
	  }
      printf(MARK "Add to global scope %s\n", s->path);
      globalscope = (dlhandle*)namedlist_add((namedlist*)globalscope, s, s->path);
   }
   return handle;
fail:
   printf(MARK "DLOPEN ERROR %s\n", prog->path);
   dlclose(handle);
   return NULL;
}

void *dlsym(void* hndl, const char* symbol)
{
   dl* s;
   void* sym;
   dlhandle* j;
   for (j = hndl; j != NULL; j = j->next) {
	  s = j->obj; 
         sym = elf_symbol(s->dl_elf->dynsym_hdr, s->dl_elf->dynsym_tab,
               s->dl_elf->dynsym_str, s->dl_elf->exec, symbol);
         if (sym) {
            return sym;
         }
   }
   return NULL;
}

int dlclose(void *hndl)
{
   dlhandle* j = hndl; 	
   dl* s;
   dlhandle* next = j;
   while (next) {
      next = j->next;
      s = j->obj;
      if (!s) continue;
      s->nlink--;
      if (s->nlink <= 0) {
         printf(MARK "Dlclose %s\n", s->path);
         elf_fini(s->dl_elf->exec, s->dl_elf->dyns, s->dl_elf->dyntab);
         namedlist_rm((namedlist*)globalscope, s->path);
	      elf_free(s->dl_elf);
         free(s->dl_elf);
         free(s);
      }
      free(j->name);
      free(j);
      j = next;
   }
   return 0;
}

void dltls(void* handle, unsigned long module_id)
{
   dlhandle* j;
   dl* s;
   for (j = handle; j != NULL; j = j->next) {
	  s = j->obj;
	  printf("DLTLS in %p(%p) elf=%p\n", s, s->path, s->dl_elf);
      int rela_ndx;
      for (rela_ndx = 0; s->dl_elf->rela[rela_ndx]; rela_ndx++) {
         if (s->dl_elf->tlsrela[rela_ndx]->relas) {
			 int i;
			 for (i = 0; i < s->dl_elf->tlsrela[rela_ndx]->count; i++)
			 {
				 *(Elf_Xword*)(s->dl_elf->exec + s->dl_elf->tlsrela[rela_ndx]->relas[i].r_offset) = module_id;
			 }
         }
      }
      s->dl_elf->tls_index = module_id;
   }
}
