#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <string.h>
#include <stdio.h>

static char* tls_initaddr = NULL;
static size_t tls_size = 0;
static char** dtv = NULL;

void* allocate_tls(size_t m, char* initaddr)
{
   tls_initaddr = initaddr;
   tls_size = m;
   return initaddr;
}

typedef struct
{
   unsigned long int ti_module;
   unsigned long int ti_offset;
} tls_index;

void *__tls_get_addr (tls_index *ti)
{
   unsigned long ti_module = ti->ti_module;
   unsigned long ti_offset = ti->ti_offset;
   if (!dtv) {
      struct rlimit r;
      getrlimit(RLIMIT_NPROC, &r);
      dtv = calloc(r.rlim_max, sizeof(char*));
   }
   if (!dtv[ti_module])
   {
//      printf("ALLOCTLS module=%ld, start=%p, size=%ld\n", ti_module, tls_initaddr, tls_size); /* GARBAGE */
      dtv[ti_module] = calloc(1, tls_size);
      memcpy(dtv[ti_module], tls_initaddr, tls_size);
   }
   return dtv[ti_module] + ti_offset;
}

__attribute__ ((destructor)) void free_tls(void)
{
   struct rlimit r;
   getrlimit(RLIMIT_NPROC, &r);
   unsigned long i;
   if (dtv) {
      for (i = 0; i < r.rlim_max; i++)
      {
         if (dtv[i]) {
             free(dtv[i]);
         }
      }
      free(dtv);
   }
}

