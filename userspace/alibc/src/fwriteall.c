#include <stdio.h>

size_t fwriteall(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t len = 0;
    size_t ret;
    while(1) {
	ret = fwrite(ptr, size, nmemb, stream);
	len += ret;
	if (len >= size * nmemb) break;
	if (!ret && feof(stream)) break;
    }
    return len;
}
