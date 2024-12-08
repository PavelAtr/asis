#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

char* execpath(const char* path, const char* file)
{
    short found = 0;
    size_t pathlen = 0;
    char* system_path = NULL;
    if (path)
    {
        system_path = strdup(path);
	pathlen = strlen(system_path);
    }
    char* rezult = malloc(pathlen + strlen(file) + 2);

    if (file[0] == '/' || !system_path)
    {
        strcpy(rezult, file);
	goto end;
    }
    char* dir = strtok(system_path, ":");
    while (dir != NULL) {
        strcpy(rezult, dir);
        strcpy(rezult + strlen(dir), file);
        dir =strtok(NULL, ":");
	struct stat st;
	if (stat(rezult, &st) != -1)
	{
    	    found = 1;
    	    break;
	}
    }
end:
    if (system_path)
	free(system_path);
    if (found)
	return rezult;
    else
	return NULL;
}
