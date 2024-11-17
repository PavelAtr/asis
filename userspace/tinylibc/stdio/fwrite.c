#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

inline size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t ret = syscall(SYS_FWRITE, stream->file, ptr, size * nmemb, stream->pos);
    stream->pos += ret;
    if (stream->pos >= stream->size)
    {
	stream->flags |= FILE_EOF;
	stream->size =  stream->pos;
    }
//    if (!ret) usleep(1);
    return ret;
}
