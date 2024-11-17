#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <tiny.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        puts("Usage: touch <path>\n");
        return -1;
    }

    int fd = open(argv[1], O_CREAT|O_RDONLY);

    if (fd == -1)
    {
	puts(strerror(errno));
	puts("\n");
	return -1;
    }

    return 0;
}
