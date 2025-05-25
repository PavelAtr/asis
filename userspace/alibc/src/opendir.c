#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

DIR *opendir(const char *dirname)
{
   char* name = fullpath(get_current_dir_name(), dirname);
   struct stat st;
   if (stat(name, &st)) {
      errno = ENOENT;
      return NULL;
   }
   if (!(st.st_mode & S_IFDIR)) {
      errno = ENOTDIR;
      return NULL;
   }
   DIR* d = malloc(sizeof(DIR));
   d->dir = name;
   d->ndx = 0;
   return d;
}
