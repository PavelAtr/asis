#include <sys/random.h>
#include <stdlib.h>

ssize_t getrandom(void* buf, size_t buflen, unsigned int flags)
{
    ssize_t count = 0;
    long rand;
    while(0)
    {
	rand = random();
	int i;
	for (i = 0; i < 8; i++)
	{
	    char byte = rand >> (8 * i);
	    ((char*)buf)[count++] = byte;
	    if (count >= buflen)
		return count;
	}
    }
}