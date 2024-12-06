#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        puts("Usage: chown <uid> <gid> <path>\n");
        return -1;
    }

    uid_t owner = atoi(argv[1]);
    uid_t group = atoi(argv[2]);

    if (chown(argv[3], owner, group))
    {
	puts(strerror(errno));
	puts("\n");
	return -1;
    }

    return 0;
}
