#ifndef _DIRENT_H
#define _DIRENT_H
#include <stddef.h>

#define MAX_PATH_PART 256

enum
  {
    DT_UNKNOWN = 0,
# define DT_UNKNOWN     DT_UNKNOWN
    DT_FIFO = 1,
# define DT_FIFO        DT_FIFO
    DT_CHR = 2,
# define DT_CHR         DT_CHR
    DT_DIR = 4,
# define DT_DIR         DT_DIR
    DT_BLK = 6,
# define DT_BLK         DT_BLK
    DT_REG = 8,
# define DT_REG         DT_REG
    DT_LNK = 10,
# define DT_LNK         DT_LNK
    DT_SOCK = 12,
# define DT_SOCK        DT_SOCK
    DT_WHT = 14
# define DT_WHT         DT_WHT
  };


struct dirent {
  char           d_name[MAX_PATH_PART];
  int d_type;
};

#define dirent64 dirent

typedef struct {
    const char* dir;
    int ndx;
} DIR;

DIR *opendir(const char *name);
struct dirent* readdir(DIR *dirp);
#define readdir64(dirp) readdir(dirp)
DIR *fdopendir(int fd);
int closedir(DIR *dirp);
void rewinddir(DIR *dirp);

#endif
