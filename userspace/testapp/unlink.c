#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
	puts("Usage: unlink <path>\n");
	return -1;
    }

    if (unlink(argv[1]))
    {
	puts(strerror(errno));
	puts("\n");
	return -1;
    }

    return 0;
}
