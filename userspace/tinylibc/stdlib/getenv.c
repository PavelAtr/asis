#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern char** environ;

int envid(const char *name);
int envnewid();

const char *getenv(const char *name)
{
    int i = envid(name);
    if (i == -1)
	return NULL;
    return &(environ[i])[strlen(name) + 1];
}

