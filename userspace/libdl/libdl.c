#include "libdl.h"
#include "dlfcn.h"
#include <stddef.h>
#include <string.h>
#define __off_t_defined
#define __time_t_defined
#define __ssize_t_defined
#include <sys/stat.h>
#include <stdio.h>
#include <sys/mman.h>

#ifdef __ASIS__
#include <asis.h>
#define stat(p, s) sys_stat(p, s)
#else
#include <stdlib.h>
#endif

void elf_free(elf *e)
{
   if (!e)
   {
      return;
   }
      freenull(&e->hdr);
      freenull(&e->phdrs);
       freenull(&e->shdrs);
      freenull(&e->shstr);
   int ndx;
   for (ndx = 0; e->rela[ndx]; ndx++)
   {
      if (e->rela[ndx])
      {
         if (e->rela[ndx]->relas)
         {
            freenull(&e->rela[ndx]->relas);
         }
         freenull(&e->rela[ndx]);
      }
   }
      freenull(&e->rela);
      freenull(&e->dyntab);
      freenull(&e->dynstr);
   if (e->exec)
      munmap(e->exec, e->exec_size);
   e->exec = NULL;
}
   

int dlload(dl *buf, const char *file)
{
   printf(MARK "Loading %s ... \n", file);
   buf->path = strdup(file);
   buf->dl_elf = calloc(1, sizeof(elf));
   buf->dl_elf->hdr = elf_load_hdr(file);
   buf->dl_elf->phdrs = elf_load_phdrs(file, buf->dl_elf->hdr);
   buf->dl_elf->exec_size = elf_load_exec(file, buf->dl_elf->hdr,
                                          buf->dl_elf->phdrs, NULL, &buf->dl_elf->tls_size, &buf->dl_elf->tls_initaddr);
   buf->dl_elf->exec = mmap(NULL, buf->dl_elf->exec_size,
                            PROT_READ | PROT_WRITE | PROT_EXEC,
                            MAP_ANONYMOUS | MAP_SHARED, -1, 0);
   memset(buf->dl_elf->exec, 0x0, buf->dl_elf->exec_size);
   elf_load_exec(file, buf->dl_elf->hdr, buf->dl_elf->phdrs, buf->dl_elf->exec,
                 &buf->dl_elf->tls_size, &buf->dl_elf->tls_initaddr);
   buf->dl_elf->shdrs = elf_load_shdrs(file, buf->dl_elf->hdr);
   if (!buf->dl_elf->hdr || !buf->dl_elf->phdrs || !buf->dl_elf->shdrs)
   {
      goto fail;
   }
   buf->dl_elf->shstr = elf_load_shstrings(file, buf->dl_elf->hdr, buf->dl_elf->shdrs);
   int start_ndx = 0;
   int relacnt = elf_count_section(buf->dl_elf->hdr, buf->dl_elf->shdrs, SHT_RELA);
   buf->dl_elf->rela = malloc((relacnt + 1) * sizeof(elfrelas *));
   int i;
   for (i = 0; i < relacnt; i++)
   {
      buf->dl_elf->rela[i] = malloc(sizeof(elfrelas));
      buf->dl_elf->rela[i]->head = elf_find_section_bytype(buf->dl_elf->hdr,
                                                           buf->dl_elf->shdrs, &start_ndx, SHT_RELA);
      if (buf->dl_elf->rela[i]->head)
      {
         buf->dl_elf->rela[i]->relas = elf_load_section(file, buf->dl_elf->hdr,
                                                        buf->dl_elf->rela[i]->head);
      }
      start_ndx++;
   }
   buf->dl_elf->rela[i] = NULL;
   start_ndx = 0;
   buf->dl_elf->dynsym_hdr = elf_find_section_bytype(buf->dl_elf->hdr, buf->dl_elf->shdrs,
                                                     &start_ndx, SHT_DYNSYM);
   if (buf->dl_elf->dynsym_hdr)
   {
      buf->dl_elf->dynsym_tab = (Elf_Sym *)(buf->dl_elf->exec + buf->dl_elf->dynsym_hdr->sh_offset);
      buf->dl_elf->dynsym_str = buf->dl_elf->exec + buf->dl_elf->shdrs[buf->dl_elf->dynsym_hdr->sh_link].sh_offset;
   }
   start_ndx = 0;
   buf->dl_elf->symtab_hdr = elf_find_section_bytype(buf->dl_elf->hdr, buf->dl_elf->shdrs,
                                                     &start_ndx, SHT_SYMTAB);
   if (buf->dl_elf->symtab_hdr)
   {
      buf->dl_elf->symtab_tab = (Elf_Sym *)(buf->dl_elf->exec + buf->dl_elf->symtab_hdr->sh_offset);
      buf->dl_elf->symtab_str = buf->dl_elf->exec + buf->dl_elf->shdrs[buf->dl_elf->symtab_hdr->sh_link].sh_offset;
   }
   start_ndx = 0;
   buf->dl_elf->dyns = elf_find_section_bytype(buf->dl_elf->hdr, buf->dl_elf->shdrs,
                                               &start_ndx, SHT_DYNAMIC);
   /*if (buf->dl_elf->dyns) {
      buf->dl_elf->dyntab = (Elf_Dyn*)(buf->dl_elf->exec + buf->dl_elf->dyns->sh_offset);
      buf->dl_elf->dynstr = buf->dl_elf->exec + buf->dl_elf->shdrs[buf->dl_elf->dyns->sh_link].sh_offset;
   }*/
   if (buf->dl_elf->dyns)
   {
      buf->dl_elf->dyntab = elf_load_section(file, buf->dl_elf->hdr, buf->dl_elf->dyns);
      buf->dl_elf->dynstr = elf_load_strings(file, buf->dl_elf->hdr, buf->dl_elf->shdrs, buf->dl_elf->dyns);
   }
   buf->module_id = max_module_count++;
   printf("%s\n", "OK");
   return 0;
fail:
   elf_free(buf->dl_elf);
   return -1;
}

dlhandle *relascope;
dlhandle *selfscope;
dlhandle *globalscope = NULL;
int max_module_count = 0;


Elf_Sym* dlsym2(void *hndl, const char *symbol, dl** out)
{
   dl *s;
   Elf_Sym* sym;
   dlhandle *j;
   for (j = hndl; j != NULL; j = j->next)
   {
      s = j->obj;
      sym = elf_symbol(s->dl_elf->dynsym_hdr, s->dl_elf->dynsym_tab,
                       s->dl_elf->dynsym_str, s->dl_elf->exec, symbol);
      if (sym)
      {
         printf(MARK "Found symbol %s in %s\n", symbol, s->path);
         *out = s;
         return sym;
      }
   }
   out = NULL;
   return NULL;
}

void *dlsym(void *hndl, const char *symbol)
{
   dl *s;
   Elf_Sym* sym;
   dlhandle *j;
   for (j = hndl; j != NULL; j = j->next)
   {
      s = j->obj;
      sym = elf_symbol(s->dl_elf->dynsym_hdr, s->dl_elf->dynsym_tab,
                       s->dl_elf->dynsym_str, s->dl_elf->exec, symbol);
      if (sym)
      {
         printf(MARK "Found symbol %s in %s\n", symbol, s->path);
         return s->dl_elf->exec + sym->st_value;
      }
   }
   return NULL;
}

void *resolve(const char *symname)
{
   void *addr = dlsym(selfscope, symname);
   if (addr)
   {
      return addr;
   }
   return dlsym(relascope, symname);
}

Elf_Sym* resolve2(const char *symname, dl** out)
{
   Elf_Sym* sym= dlsym2(selfscope, symname, out);
   if (sym)
   {
      return sym;
   }
   return dlsym2(relascope, symname , out);
}


char *ldpath(const char *path, const char *file)
{
   short found = 0;
   size_t pathlen = 0;
   char *system_path = NULL;
   if (path)
   {
      system_path = strdup(path);
      pathlen = strlen(system_path);
   }
   char *rezult = malloc(pathlen + strlen(file) + 2);
   if (file[0] == '/' || !system_path)
   {
      strcpy(rezult, file);
      goto end;
   }
   char *dir = strtok(system_path, ":");
   while (dir != NULL)
   {
      strcpy(rezult, dir);
      strcpy(rezult + strlen(dir), "/");
      strcpy(rezult + strlen(dir) + 1, file);
      struct stat st;
      if (stat(rezult, &st) != -1)
      {
         found = 1;
         break;
      }
      dir = strtok(NULL, ":");
   }
end:
   if (system_path)
   {
      free(system_path);
   }
   if (found)
   {
      return rezult;
   }
   else
   {
      return NULL;
   }
}

void *dlopen(const char *filename, int flags)
{
   dl *prog = calloc(1, sizeof(dl));
   dlhandle *handle = NULL;
   if (dlload(prog, filename) == -1)
   {
      goto fail;
   }
   handle = (dlhandle *)list_add(NULL, prog);
#ifdef USE_SYMBOLFILE
   FILE *symfile = fopen("dl.txt", "a");
   fprintf(symfile, "add-symbol-file %s ", prog->path);
   elf_print_sections_symbols(symfile, prog->dl_elf->exec, prog->dl_elf->hdr, prog->dl_elf->shdrs, prog->dl_elf->shstr);
   fprintf(symfile, "\n");
   fclose(symfile);
#endif
   dlhandle *j;
   list_geteach_once;
   for (j = handle; j; j = j->next)
   {
      dl *s = j->obj;
      const char *file;
      int dtneed_ndx = 0;
      while ((file = elf_dtneed(s->dl_elf->dyns, s->dl_elf->dyntab,
                                s->dl_elf->dynstr, &dtneed_ndx)))
      {
         char *path = ldpath(ld_library_path, file);
         if (!path)
         {
            printf(MARK "%s not found in %s\n", file, ld_library_path);
            goto fail;
         }
         char found = 0;
         list_geteach(handle)
         {
            if (strcmp(((dl *)fndlist->obj)->path, path) == 0)
            {
               printf(MARK "Needed %s alredy\n", path);
               found = 1;
               break;
            }
         }
         if (found)
            continue;
         dl* lib;
	 dl* glib = NULL;
         list_geteach(globalscope)
         {
            if (strcmp(((dl *)fndlist->obj)->path, path) == 0)
            {
               printf(MARK "InCache %s\n", path);
               glib = fndlist->obj;
               break;
            }
         }
         if (glib)
	{
	    handle = (dlhandle *)list_add((list*) handle, glib);
	    glib->nlink++;
	}
	else
         {
            lib = calloc(1, sizeof(dl));
            if (dlload(lib, path) == -1)
               goto fail;
            lib->nlink = 1;
            handle = (dlhandle *)list_add((list*)handle, lib);
            globalscope = (dlhandle *)list_add((list *)globalscope, lib);
            free(path);
#ifdef USE_SYMBOLFILE
            FILE *symfile = fopen("dl.txt", "a");
            fprintf(symfile, "add-symbol-file %s ", lib->path);
            elf_print_sections_symbols(symfile, lib->dl_elf->exec, lib->dl_elf->hdr, lib->dl_elf->shdrs, lib->dl_elf->shstr);
            fprintf(symfile, "\n");
            fclose(symfile);
#endif
         }
      }
   }
   relascope = handle;
    list_geteach(handle)
   {
      dl *s = fndlist->obj;
      if (s->status & DL_RELOCATED)
      {
         printf(MARK "Alredy relocated %s\n", s->path);
         continue;
      }
      printf(MARK "Relocate %s\n", s->path);
      selfscope = (dlhandle*) fndlist;
      int rela_ndx;
      for (rela_ndx = 0; s->dl_elf->rela[rela_ndx]; rela_ndx++)
      {
         int tls_relas_count = 0;
         elf_relocate(s->dl_elf->hdr, s->dl_elf->rela[rela_ndx]->head,
                      s->dl_elf->rela[rela_ndx]->relas, s->dl_elf->dynsym_tab,
                      s->dl_elf->dynsym_str, &tls_relas_count, s->dl_elf->exec, &resolve);
         elf_relocate_tls(s->dl_elf->rela[rela_ndx]->head, s->dl_elf->rela[rela_ndx]->relas,
            s, &resolve2);
      }
   s->tls_size = s->dl_elf->tls_size;
      s->status |= DL_RELOCATED;
   }
    list_geteach(handle)
   {
      dl *s = fndlist->obj;
      if (s->status & DL_INITED)
      {
         continue;
      }
      printf(MARK "Init %s\n", s->path);
      elf_init(s->dl_elf->exec, s->dl_elf->dyns, s->dl_elf->dyntab);
      s->status |= DL_INITED;
   }

   return handle;
fail:
   printf(MARK "DLOPEN ERROR %s\n", prog->path);
   dlclose(handle);
   return NULL;
}

int dlclose(void *hndl)
{
   dlhandle *j = hndl;
   dl *s;
   dlhandle *next = j;
   dlhandle *copy = j;
   while (next)
   {
      next = j->next;
      s = j->obj;
      if (!s)
         continue;
      s->nlink--;
      if (s->nlink <= 0)
      {
         printf(MARK "Dlclose %s nlink=%d\n", s->path, s->nlink);
         globalscope = (dlhandle*) list_rm((list*) globalscope, s);
	 copy = (dlhandle*) list_rm((list*) copy, s);
         elf_fini(s->dl_elf->exec, s->dl_elf->dyns, s->dl_elf->dyntab);
         elf_free(s->dl_elf);
         freenull(&s->dl_elf);
         freenull(&s);
      }
      j = next;
   }
   return 0;
}

void tls_init(dl* s, char* dest, size_t tls_size)
{
   if (!s->dl_elf->tls_initaddr)
   {
      return;
   }
   memcpy(dest, s->dl_elf->tls_initaddr, s->tls_size);
}

#define R_DTPMOD64 R_X86_64_DTPMOD64
#define R_DTPOFF64 R_X86_64_DTPOFF64


void elf_relocate_tls(Elf_Shdr* rela, Elf_Rela* relatab, dl* s, Elf_Sym* (*resolve2)(const char *symname, dl** out))
{
   int j;
   Elf_Sym* sym;
   dl* out;
   const char* symname;
   if (!rela || !relatab || !s || !s->dl_elf || !s->dl_elf->exec)
   {
      printf(MARK "%s  %p %p %p\n", "elf_relocate_tls: hdrs is NULL",
         rela, relatab, s);
      return;
   }
   for(j = 0; j < (int)(rela->sh_size / rela->sh_entsize); j ++) {
      switch (ELF_R_TYPE(relatab[j].r_info)) {
         case R_DTPMOD64:
            symname = &s->dl_elf->dynsym_str[s->dl_elf->dynsym_tab[ELF_R_SYM(relatab[j].r_info)].st_name];
            if (resolve2) {
               sym = resolve2(symname, &out);
            }
            if (!out) {
               break;
            }
            printf(MARK "Relocating TLS %s in %s from %s\n", symname, s->path, out->path);
            *(Elf_Xword *)(s->dl_elf->exec + relatab[j].r_offset) = out->module_id;
            break;
         case R_DTPOFF64:
            symname = &s->dl_elf->dynsym_str[s->dl_elf->dynsym_tab[ELF_R_SYM(relatab[j].r_info)].st_name];
            if (resolve2) {
               sym = resolve2(symname, &out);
            }
            printf(MARK "Relocating TLS %s in %s from %s\n", symname, s->path, out->path);
            if (!sym) {
               break;
            }
            if (sym->st_shndx == SHN_UNDEF) {
               break;
            }
            *(Elf_Xword *)(s->dl_elf->exec + relatab[j].r_offset) = sym->st_value;
            break;
         default:
            break;
      }	   
   }
}

