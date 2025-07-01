/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include "../../config.h"
#include "../include/asis.h"

#undef malloc
#undef calloc
#undef realloc
#undef mmap
#undef munmap
#undef free


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


void init_memory(void* base, size_t size)
{
}

int_t empty_memreg()
{
   int i;
   for (i = 0; i < MAXMEMREG; i++) {
      if ((*current->memregs)[i].addr == NULL) {
         (*current->memregs)[i].addr = (void*) 0x01;
         return i;
      }
   }
   return -1;
}

int_t get_memreg(void* addr)
{
   int i;
   for (i = 0; i < MAXMEMREG; i++) {
      if ((*current->memregs)[i].addr == addr) {
         return i;
      }
   }
   return -1;
}

void free_memreg(int_t index)
{
   if (index < 0 || index >= MAXMEMREG) {
      return; // Invalid index
   }
   (*current->memregs)[index].addr = NULL;
   (*current->memregs)[index].size = 0;
}

void set_memreg(int_t index, void* addr, size_t size)
{
   if (index < 0 || index >= MAXMEMREG) {
      return; // Invalid index
   }
   (*current->memregs)[index].addr = addr;
   (*current->memregs)[index].size = size;
}

size_t sys_malloc_usable_size(void *ptr)
{
   if (!ptr) {
      return 0; // If the pointer is NULL, return 0
   }
   int_t index = get_memreg(ptr);
   if (index >= 0) {
      return (*current->memregs)[index].size; // Return the size from the memory registry
   }
   // If the memory region was not found, we can assume it's a standard malloc allocation
   // and return a default size (this is implementation-specific).
   // In practice, you might want to use platform-specific functions to get the size.
   return 0; // Default case, size unknown
}

#ifdef CONFIG_LINUX
void *sys_mmap(void* addr, size_t size, int prot, int flags, int f,
   off_t offset)
{
   return mmap(addr, size, prot, flags, f, offset);
}

int sys_munmap(void* addr, size_t length)
{
   return munmap(addr, length);
}
#endif
#ifdef CONFIG_UEFI
void* sys_mmap(void* addr, size_t size, int prot, int flags, int f,
   off_t offset)
{
   return malloc(size);
}  
int sys_munmap(void* addr, size_t length)
{
   free(addr);
   return 0; // Success
}
#endif



void* sys_malloc(size_t size)
{
   void* ret = malloc(size);
   if (current->memregs) {
      int i = empty_memreg();
      set_memreg(i, ret, size);
   }
   return ret;
}

void* sys_calloc(size_t nmemb, size_t size)
{
   void* ret = calloc(nmemb, size);
   if (current->memregs) {
      int i = empty_memreg();
      set_memreg(i, ret, nmemb * size);
   }
   return ret;
}

void* hyperv_malloc(size_t size)
{
   return malloc(size);
}

void* hyperv_calloc(size_t nmemb, size_t size)
{
   return calloc(nmemb, size);
}

void* sys_realloc(void* ptr, size_t new_size) {
   if (new_size == 0) {
      free_memreg(get_memreg(ptr));
      sys_free(ptr);
      return NULL;
   }
   void* ret = malloc(new_size);
   if (ptr) {
      int_t index = get_memreg(ptr);
      if (index >= 0) {
         size_t old_size = (*current->memregs)[index].size;
         memcpy(ret, ptr, old_size < new_size ? old_size : new_size);
         sys_free(ptr);
      } else {
         // If the memory region was not found, we just copy the data
         // from the old pointer to the new one, but we won't free it.
         // This is a fallback case, not ideal but necessary for safety.
         memcpy(ret, ptr, new_size);
      }
   }
   set_memreg(empty_memreg(), ret, new_size);
   return ret;
}

void sys_freenull(void **ptr)
{
   if (!*ptr) {
      return; // Nothing to free
   }
   free_memreg(get_memreg(*ptr));
   free(*ptr);
   *ptr = NULL; // Set pointer to NULL after freeing  
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
