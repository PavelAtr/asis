#include "dummyblk.h"

len_t blk_read(void* devsb, void* ptr, len_t size)
{
   return 0;
}

len_t blk_write(void* devsb, const void* ptr, len_t size)
{
   return 0;
}

void blk_seek(void* devsb, len_t offset)
{
}

errno_t blk_ioctl(void* devsb, ulong_t request, va_list vl)
{
   return 0;
}
