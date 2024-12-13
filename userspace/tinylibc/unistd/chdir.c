#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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