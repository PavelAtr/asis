#include "block.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>

int fd;
char* BLOCK_DEV;

void block_open()
{
   fd = open(BLOCK_DEV, O_RDWR);
   if (fd < 0) {
      error(ENOENT, ENOENT, "Fail open %s\n", BLOCK_DEV);
   }
}

void block_seek(void* devparam, len_t offset)
{
   lseek(fd, offset, SEEK_SET);
}

len_t block_write(void* devparam, const void* buffer, len_t size)
{
   return write(fd, buffer, size);
}

len_t block_read(void* devparam, void* buffer, len_t size)
{
   return read(fd, buffer, size);
}

