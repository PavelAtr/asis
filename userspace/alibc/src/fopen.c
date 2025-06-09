#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <syscall.h>

FILE* fopen(const char* path, const char* mode)
{
   struct stat st;
   if (stat(path, &st)) {
      errno = ENOENT;
      return NULL;
   }
   FILE* ret = calloc(1, sizeof(FILE));
   initfile(ret);
   char* cwd = get_current_dir_name();
   ret->file = fullpath(cwd, path);
   ret->size = st.st_size;
   if (st.st_mode & S_IFCHR) {
      ret->flags |= FILE_INFINITY;
   }
   if (st.st_mode & S_IFIFO ) {
      ret->pipbuf = asyscall(SYS_SHARED, "fifo", ret->file, mode, 0, 0, 0);
   }
   if (ret->pipbuf) {
      ret->flags |= FILE_INFINITY;
      ret->pipbuf->nlink++;
   }
   return ret;
}
