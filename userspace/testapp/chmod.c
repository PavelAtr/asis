#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        puts("Usage: chmod <mode> <path>\n");
        return -1;
    }

    mode_t mode = atoi(argv[1]);

    if (chmod(argv[2], mode))
    {
	puts(strerror(errno));
	puts("\n");
	return -1;
    }

    return 0;
}
