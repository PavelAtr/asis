/*
 * TLS (Thread-Local Storage) Initialization and Access
 *
 * This file provides basic functions for managing thread-local storage (TLS)
 * in a userspace environment. It includes allocation, access, and cleanup
 * routines for TLS blocks.
 *
 * Globals:
 *   - tls_initaddr: Pointer to the initial TLS data.
 *   - tls_size: Size of the TLS block.
 *   - dtv: Dynamic Thread Vector, an array of pointers to TLS blocks per module.
 *
 * Functions:
 *   void* allocate_tls(size_t m, char* initaddr)
 *     - Initializes the TLS system with a given size and initial data address.
 *     - Parameters:
 *         m: Size of the TLS block.
 *         initaddr: Pointer to the initial TLS data.
 *     - Returns: The initial address of the TLS data.
 *
 *   typedef struct {
 *     unsigned long int ti_module;
 *     unsigned long int ti_offset;
 *   } tls_index;
 *     - Structure representing the TLS index, specifying the module and offset.
 *
 *   void* __tls_get_addr(tls_index *ti)
 *     - Retrieves the address of the TLS variable for the given index.
 *     - Allocates and initializes the TLS block for the module if not already done.
 *     - Parameters:
 *         ti: Pointer to a tls_index structure specifying module and offset.
 *     - Returns: Pointer to the TLS variable at the specified offset.
 *
 *   void free_tls(void)
 *     - Destructor function to free all allocated TLS blocks and the DTV array.
 *     - Automatically called on program exit.
 */
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <string.h>
#include <stdio.h>

extern char* origin;

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
   printf("__tls_get_addr: module=%lu, offset=%lu in %s\n", ti_module, ti_offset, origin); /* GARBAGE */
   if (!dtv) {
      struct rlimit r;
      getrlimit(RLIMIT_NPROC, &r);
      dtv = calloc(r.rlim_max, sizeof(char*));
   }
   if (!dtv[ti_module])
   {
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
             printf("Freeing TLS for module %lu in %s\n", i, origin); /* GARBAGE */
             free(dtv[i]);
             dtv[i] = NULL;
         }
      }
      free(dtv);
      dtv = NULL;
   }
}

