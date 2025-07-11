/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

DIR *opendir(const char *dirname)
{
   char temp[PATHMAX];
   char* pwd = get_current_dir_name();
   char* name = strdup(fullpath(temp, pwd, dirname));
   free(pwd);
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
   d->type = F_DIR;
   initfile((FILE*)d);
   d->file = name;
   d->ndx = 0;
   return d;
}
