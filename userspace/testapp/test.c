#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	char s[1024];
	size_t size = snprintf(s, 100 ,"Hello world s=%s d=%d f=%f\n", "string", 1000, 1.0156);
	puts(s);

	return size;
}
