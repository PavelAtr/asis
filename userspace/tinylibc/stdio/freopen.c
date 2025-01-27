#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

FILE *freopen(const char* path, const char* mode,
     FILE* stream)
{
   if (stream->file) {
      free(stream->file);
   }
   struct stat st;
   if (stat(path, &st)) {
      errno = ENOENT;
      return NULL;
   }
   stream->file = fullpath(getenv("CWD"), path);
   stream->size = st.st_size;
   stream->pos = 0;
   stream->flags = 0;
   stream->strbuf = NULL;
   if (st.st_mode & (S_IFCHR)) {
      stream->flags |= FILE_INFINITY;
   }
   return stream;
}

