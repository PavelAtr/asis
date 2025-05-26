#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>

int* tinylibc_tls_id = NULL;
size_t tls_size = 256;
char** dtv = NULL;

void* allocate_tls(size_t m)
{
   tls_size = m;
   return NULL;
}

typedef struct
{
   unsigned long int ti_module;
   unsigned long int ti_offset;
} tls_index;

__attribute__ ((visibility ("hidden"))) void *__tls_get_addr (tls_index *ti)
{
   unsigned long ti_module = ti->ti_module;
   unsigned long ti_offset = ti->ti_offset;
   if (!dtv) {
      struct rlimit r;
      getrlimit(RLIMIT_NPROC, &r);
      dtv = calloc(1, sizeof(char*) * r.rlim_max);
   }
   if (!dtv[ti_module])
   {
      dtv[ti_module] = calloc(1, tls_size);
   }
   return dtv[ti_module] + ti_offset;
}

__attribute__ ((destructor)) void free_tls(void)
{
   struct rlimit r;
   getrlimit(RLIMIT_NPROC, &r);
   long i;
   if (dtv) {
      for (i = 0; i < r.rlim_max; i ++)
      {
         if (dtv[i]) {
             free(dtv[i]);
         }
      }
      free(dtv);
   }
}

