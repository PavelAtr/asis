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
   size_t cwdsize;
   if ((cwdsize = strlen(cwd)) > size - 1)
   {
      errno = ERANGE;
      return NULL;
   }
   memset(buf, 0x0, size);
   strncpy(buf, cwd, cwdsize);

   return buf;
}
