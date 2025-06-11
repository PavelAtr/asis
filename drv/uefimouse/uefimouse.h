#ifndef _TTY_H
#define _TTY_H
#include "../../core/include/sys/types.h"

len_t uefimouse_read(void* devsb, void* ptr, len_t size);
len_t uefimouse_write(void* devsb, const void* ptr, len_t size);
void uefimouse_seek(void* devsb, len_t offset);
errno_t uefimouse_ioctl(void* devsb, ulong_t request, void* arg1, void* arg2, void* arg3, void* arg4);

#endif
