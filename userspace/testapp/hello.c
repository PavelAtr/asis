#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	size_t size = fprintf(stdout, "Hello world s=%s d=%d f=%f\n", "string", 1000, 1.0156);

	return size;
}
