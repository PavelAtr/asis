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
   if (stat(path, &st)) {
      errno = ENOENT;
      return NULL;
   }
   FILE* ret = malloc(sizeof(FILE));
   initfile(ret);
   ret->file = fullpath(get_current_dir_name(), path);
   ret->size = st.st_size;
   if (st.st_mode & (S_IFCHR)) {
      ret->flags |= FILE_INFINITY;
   }
   return ret;
}
