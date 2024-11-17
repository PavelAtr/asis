#ifndef _DIRENT_H
#define _DIRENT_H
#include <stddef.h>

#define MAX_PATH_PART 256

struct dirent {
   char           d_name[MAX_PATH_PART];
};

typedef struct {
    const char* dir;
    int ndx;
} DIR;

DIR *opendir(const char *name);
struct dirent* readdir(DIR *dirp);

#endif