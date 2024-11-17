#ifndef _BLK_H
#define _BLK_H
#include "../../core/include/tinysys.h"

len_t blk_read(void* devsb, void* ptr, len_t size);
len_t blk_write(void* devsb, const void* ptr, len_t size);
void blk_seek(void* devsb, len_t offset);
errno_t blk_ioctl(void* devsb, ulong_t request, ...);

#endif
