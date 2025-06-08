#include <stdio.h>

size_t freadall(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t len = 0;
    while(1) {
	len += fread(ptr, size, nmemb, stream);
	if (len >= size * nmemb) break;
    if (feof(stream)) break;
    }
    return len;
}
