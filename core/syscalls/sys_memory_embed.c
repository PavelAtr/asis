#include <tinysys.h>
#include <stddef.h>
#include <string.h>

#typedef unsigned char cell;
#define cellid(addr)  ((cell)((addr & 0x3F) | 0x80))

unsigned char* memory;
size_t memsize;
off_t curpos = 0;

void init_memory(void* base, size_t size)
{
   sys_printf(SYS_INFO "Initializing memory size=%ld\n", size);
   memory = base;
   memsize = size;
   off_t i;
   for (i = 0; i < memsize; i++) {
      addr_t addr = (addr_t)(memory + i);
      memory[i] = cellid(addr);
   }
}

off_t findfree(size_t needsize)
{
   size_t founded = 0;
   off_t ret = -1;
   off_t i;
   for(i = 0; i < memsize; i++) {
      addr_t addr = (addr_t)(memory + i);
      if (memory[i] == cellid(addr)) {
         ret = (founded == 0)? i : ret;
         founded ++;
      } else {
         founded = 0;
      }
      if (founded == needsize + 2) {
         break;
      }
   }
   if (founded == needsize + 2) {
      return ret;
   }
   return -1;
}


void* sys_malloc(size_t size)
{
   off_t found = findfree(size);
   if (found == -1) {
      return NULL;
   }
   off_t i;
   for (i = found + 1; i <= found + size; i++) {
      memory[i] = 0x0;
   }
   return &memory[found + 1];;
}

size_t free_memory(void)
{
   size_t ret = 0;
   off_t i;
   for (i = 0; i < memsize; i++) {
      addr_t addr = (addr_t)(memory + i);
      if (memory[i] == cellid(addr)) {
         ret++;
      }
   }
   return ret;
}

void sys_free(void *ptr)
{
   off_t i;
   for (i = (unsigned char*)ptr - memory; i < memsize; i++) {
      addr_t addr = (addr_t)memory[i];
      if (memory[i] == cellid(addr)) {
         break;
      } else {
         memory[i] = cellid(addr);
      }
   }
}



void* sys_mmap(void* addr, size_t size, int prot, int flags, int f,
   off_t offset)
{
   return sys_malloc(size);
}

int sys_munmap(void* addr, size_t length)
{
   sys_free(addr);
   return 0;
}



