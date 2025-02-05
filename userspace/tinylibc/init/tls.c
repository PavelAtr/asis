#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/resource.h>

int* tinylibc_tls_id = NULL;
size_t tls_size = 0;

void* allocate_tls(size_t m)
{
   tls_size = m;
   return NULL;
}

__thread FILE*** core_fds2;

int a;

typedef struct
{
   unsigned long int ti_module;
   unsigned long int ti_offset;
} tls_index;

__attribute__ ((visibility ("hidden"))) void *__tls_get_addr (tls_index *ti)
{
   unsigned long ti_module = (tinylibc_tls_id) ? *tinylibc_tls_id : ti->ti_module;
   unsigned long ti_offset = ti->ti_offset;
   struct rlimit r;
   getrlimit(RLIMIT_NPROC, &r);
   printf("TLS module=%ld offset=%ld tlssize=%ldX%ld\n", ti_module, ti_offset, tls_size, r.rlim_max);
   return &a;
}
