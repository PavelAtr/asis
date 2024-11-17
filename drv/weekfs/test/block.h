#ifndef _BLOCK_H
#define _BLOCK_H

#include "weekfs.h"

extern char* BLOCK_DEV;

void block_open();
void block_seek(void* devparam, len_t offset);
len_t block_write(void* devparam, const void* buffer, len_t size);
len_t block_read(void* devparam, void* buffer, len_t size);

#endif
