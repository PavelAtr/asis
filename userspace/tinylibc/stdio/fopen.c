#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

FILE* fopen(const char* path, const char* mode)
{
	struct stat st;
	if (stat(path, &st))
	{
	    set_errno(ENOENT);
	    return NULL;
	}
	FILE* ret = malloc(sizeof(FILE));
	ret->file = fullpath(cwd, path);
	ret->size = st.st_size;
	ret->pos = 0;
	ret->flags = 0;
	ret->strbuf = NULL;
	if (st.st_mode & (S_IFCHR))
	    ret->flags |= FILE_INFINITY;

	return ret;
}
