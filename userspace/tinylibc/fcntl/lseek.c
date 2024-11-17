#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

off_t lseek(int f, off_t offset, int whence)
{
    if (fds[f].flags & O_APPEND)
	return fds[f].stream->pos;
    return fseek(fds[f].stream, offset, whence);
}
