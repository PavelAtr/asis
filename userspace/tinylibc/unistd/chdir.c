#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int chdir(const char *path)
{
   if (path[0] == '/') {
      setenv("CWD", path, 0);
      return 0;
   }
   char* cwd = getenv("CWD");
   char* newcwd = malloc(strlen(cwd) + strlen(path) + 1);
   strcpy(newcwd, cwd);
   strcpy(newcwd + strlen(cwd), path);
   setenv("CWD", newcwd, 0);
   free(newcwd);
   return 0;
}

char *get_current_dir_name(void)
{
   return getenv("CWD");
}

char *getcwd(char* buf, size_t size)
{
   char* cwd = getenv("CWD");
   size_t cwdsize = strlen(cwd);
   size_t bufsize = size;
   char* ret = buf;
   if (!buf) {
      if (!size) {
         bufsize = cwdsize + 1;
         ret = malloc(bufsize);
      } else {
         if (cwdsize >= size) {
            errno = ERANGE;
            return NULL;
         }
         bufsize = size;
         ret = malloc(bufsize);
      }
   }
   if (cwdsize >= bufsize)
   {
      errno = ERANGE;
      return NULL;
   }
   memset(ret, 0x0, bufsize);
   strncpy(ret, cwd, cwdsize);

   return ret;
}
