#ifndef UEFI
#include <sys/mman.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#else
#include "../uefi/uefi.h"
#endif

#define cellid(addr)  ((addr & 0x7F) | 0x80)

void init_memory(void* base, size_t size)
{
}


void *sys_mmap(void* addr, size_t size, int prot, int flags, int f, off_t offset)
{
#ifdef UEFI
   return malloc(size);
#else
   return mmap(addr, size, prot, flags, f, offset);
#endif
}

int sys_munmap(void* addr, size_t length)
{
#ifdef UEFI
   free(addr);
   return 0;
#else
   return munmap(addr, length);
#endif
}


void* sys_malloc(size_t size)
{
   return malloc(size);
}

void sys_free(void *ptr)
{
   free(ptr);
}

size_t free_memory(void)
{
   return 0;
}

