/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

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
   FILE* ret;
   if (st.st_mode & S_IFIFO ) {
      ret = calloc(1, sizeof(anamedpipe));
      ret->type = F_NAMEDPIPE;
   } else {
      ret = calloc(1, sizeof(FILE));
      ret->type = F_FILE;
   }
   initfile(ret);
   char* cwd = get_current_dir_name();
   ret->file = fullpath(cwd, path);
   ret->size = st.st_size;
   ret->mode = mode;
   if (st.st_mode & S_IFCHR) {
      ret->flags |= FILE_INFINITY;
   }
   if (st.st_mode & S_IFIFO ) {
      size_t objsize = -1;
      if ((errno = (int)asyscall(SYS_SHARED, &((anamedpipe*)ret)->pbuf,"fifo", ret->file, mode, &objsize, 0)))
	{
	    freefile(ret);
	    return NULL;
	}
      ((anamedpipe*)ret)->pbuf->refcount++;
   }
   return ret;
}
