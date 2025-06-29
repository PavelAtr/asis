#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <syscall.h>

int chdir(const char *path)
{
   char* cwd = get_current_dir_name();
   char* newcwd = alloca(strlen(cwd) + strlen(path) + 2);
   if (path[0] == '/') {
      if (path[1] == '\0') {
         // If the path is just "/", we can just change to root
         strcpy(newcwd, "/");
         goto end;
      }
      // If the path is absolute, we can just copy it
      strcpy(newcwd, path);
      strcpy(newcwd + strlen(path), "/");
      goto end;
   }
   strcpy(newcwd, cwd);
   strcpy(newcwd + strlen(cwd), path);
   strcpy(newcwd + strlen(cwd) + strlen(path), "/");
end:
   if ((errno = (int)asyscall(SYS_CHDIR, newcwd, 0, 0, 0, 0, 0))) {
      return -1; // Error occurred
   }   
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
   free(cwd);

   return ret;
}
