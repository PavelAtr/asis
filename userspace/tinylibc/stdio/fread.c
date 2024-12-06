#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t ret;
    size_t len;

    if (stream->strbuf)
    {
	len = size * nmemb;
	ret = (stream->pos + len > stream->size)? stream->size - stream->pos: len;
	size_t i;
	for (i = 0; i < ret; i++)
	    ((char*) ptr)[stream->pos + i] = stream->strbuf[i];
	return ret;
    }

    ret = syscall(SYS_FREAD, stream->file, ptr, size * nmemb, stream->pos);
    stream->pos += ret;
    if (stream->pos >= stream->size)
    {
	stream->flags |= FILE_EOF;
	stream->size = stream->pos;
    }
//    if (!ret) usleep(1);
    return ret;
}
