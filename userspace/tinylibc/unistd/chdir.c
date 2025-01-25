#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int chdir(const char *path)
{
   if (path[0] == '/') {
      strcpy(cwd, path);
      return 0;
   }
   strcpy(cwd + strlen(cwd), path);
   setenv("CWD", cwd, 0);
   return 0;
}

char *get_current_dir_name(void)
{
   return cwd;
}

char *getcwd(char* buf, size_t size)
{
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
