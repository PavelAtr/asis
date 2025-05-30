#include "../../config.h"

#ifdef CONFIG_LINUX
#include <sys/mman.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>
#endif

#ifdef CONFIG_UEFI
#include "../uefi/uefi.h"
#endif

#define cellid(addr)  ((addr & 0x7F) | 0x80)

void init_memory(void* base, size_t size)
{
}


void *sys_mmap(void* addr, size_t size, int prot, int flags, int f,
   off_t offset)
{
#ifdef CONFIG_UEFI
   return malloc(size);
#else
   return mmap(addr, size, prot, flags, f, offset);
#endif
}

int sys_munmap(void* addr, size_t length)
{
#ifdef CONFIG_UEFI
   free(addr);
   return 0;
#endif
#ifdef CONFIG_LINUX
   return munmap(addr, length);
#endif
}


void* sys_malloc(size_t size)
{
   return malloc(size);
}

void* sys_calloc(size_t nmemb, size_t size)
{
   return calloc(nmemb, size);
}


void* sys_realloc(void* ptr, size_t size)
{
	return realloc(ptr, size);
}

void sys_free(void *ptr)
{
   free(ptr);
}

size_t free_memory(void)
{
   return 0;
}

#ifdef CONFIG_UEFI
void* alloc_stack(size_t size) {
    uint64_t stack_base = 0;
    size_t pages = (size + 0xFFF) / 0x1000;
    efi_status_t status = BS->AllocatePages(
        AllocateAnyPages,
        EfiLoaderData,
        pages,
        &stack_base
    );
    if (EFI_ERROR(status)) {
        return NULL;
    }
    return (void*)stack_base;
}

void free_stack(void* stackbase, size_t size) {
    size_t pages = (size + 0xFFF) / 0x1000;
    uint64_t efistack_base = (uint64_t)stackbase;
    BS->FreePages(efistack_base, pages);
}
#endif

#ifdef CONFIG_LINUX
void* alloc_stack(size_t size) {
   return sys_malloc(size);
}

void free_stack(void* stackbase, size_t size) {
   sys_free(stackbase);
}
#endif
