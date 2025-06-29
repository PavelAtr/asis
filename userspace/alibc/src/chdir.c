#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <syscall.h>

int chdir(const char *path)
{
   const char* ret;
   char* newcwd;
   if (path[0] == '/') {
      ret = path;
      goto end;
   }
   char* cwd = getenv("CWD");
   newcwd = alloca(strlen(cwd) + strlen(path) + 1);
   strcpy(newcwd, cwd);
   strcpy(newcwd + strlen(cwd), path);
   ret = newcwd;
end:
   if ((errno = (int)asyscall(SYS_CHDIR, ret, 0, 0, 0, 0, 0))) {
      return -1; // Error occurred
   }   
   setenv("CWD", ret, 0);
   return 0;
}

char *get_current_dir_name(void)
{
   return asyscall(SYS_GETCWD, 0, 0, 0, 0, 0, 0);
}

char *getcwd(char* buf, size_t size)
{
   char* cwd = get_current_dir_name();
   if (!cwd) {
      errno = ENOENT;
      return NULL;
   }
   size_t cwdsize = strlen(cwd);
   size_t bufsize = size;
   char* ret = buf;
   if (!buf) {
      if (!size) {
         bufsize = cwdsize + 1;
      } else {
         if (cwdsize >= size) {
            errno = ERANGE;
            return NULL;
         }
         bufsize = size;
      }
      ret = malloc(bufsize);
   }
   memset(ret, 0x0, bufsize);
   strncpy(ret, cwd, cwdsize);

   return ret;
}
