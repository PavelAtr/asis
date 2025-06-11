#include <stdio.h>
#include <sys/mman.h>

int memfd_create(const char *name, unsigned int flags)
{
   return 0;
}
#define MFD_CLOEXEC 0x1

/*
FILE *fmemopen(void* buf, size_t size, const char *mode)
{
   FILE* ret = malloc(sizeof(FILE));
   initfile(ret);
   ret->file = strdup("mem");
   ret->size = size;
   ret->strbuf = buf;
   return ret;
}
*/
/*FILE* fopen(const char* path, const char* mode)
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
      size_t objsize = 0;
      ret->pipbuf = asyscall(SYS_SHARED, "fifo", ret->file, mode, &objsize, 0, 0);
   }
   if (ret->pipbuf) {
      ret->flags |= FILE_INFINITY;
      ret->pipbuf->nlink++;
   }
   return ret;
}
*/