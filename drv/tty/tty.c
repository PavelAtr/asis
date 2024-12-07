#ifndef UEFI
#include <stdio.h>
#else
#include "../../core/uefi/uefi.h"
#endif

#include "tty.h"

len_t tty_read(void* devsb, void* ptr, len_t size)
{
    int ch = getchar();
    *((int*)ptr) = ch;

    return 1;
}

len_t tty_write(void* devsb, const void* ptr, len_t size)
{
	return fwrite(ptr, size, 1, stdout);
}

void tty_seek(void* devsb, len_t offset)
{
}

errno_t tty_ioctl(void* devsb, ulong_t request, ...)
{
    return 0;
}
