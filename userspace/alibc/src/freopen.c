#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

FILE *freopen(const char* path, const char* mode,
     FILE* stream)
{
INIT_afds
   if (stream->file) {
      free(stream->file);
   }
   struct stat st;
   if (stat(path, &st)) {
      errno = ENOENT;
      return NULL;
   }
   stream->file = fullpath(get_current_dir_name(), path);
   stream->size = st.st_size;
   stream->pos = 0;
   stream->flags = 0;
   if (st.st_mode & (S_IFCHR)) {
      stream->flags |= FILE_INFINITY;
   }
   return stream;
}

