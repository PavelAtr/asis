#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int* tinylibc_tls_id = NULL;

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
   printf("TLS module=%ld offset=%ld\n", ti_module, ti_offset);
   return &a;
}
