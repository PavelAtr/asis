#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <syscall.h>

int envid(const char *name);

char** realloc_environment(char** old_env, size_t old_count, size_t new_count) {
    char** new_env = malloc(sizeof(char*) * new_count);
    if (!new_env) return NULL;
    for (size_t i = 0; i < old_count && i < new_count; ++i)
        new_env[i] = old_env[i];
    for (size_t i = old_count; i < new_count; ++i)
        new_env[i] = NULL;
    free(old_env);
    return new_env;
}

int setenv(const char *name, const char *value, int overwrite)
{
   INIT_ENVIRON
   int i = envid(name);
   if (i != -1) {
      if (!overwrite) {
         return 0; // Variable already exists and overwrite is false
      }
      free(environ[i]);
      environ[i] = malloc(strlen(name) + strlen(value) + 2);
      strcpy(environ[i], name);
      strcat(environ[i], "=");
      strcat(environ[i], value);
   } else {
      int i;
      for (i = 0; environ[i]; i++);
      environ = realloc_environment(environ, i, i + 1);
      *core_environ = environ;
      if (!environ) {
         return -1; // Memory allocation failed
      }
      environ[i + 1] = NULL; // Null-terminate the new environment array
      environ[i] = malloc(strlen(name) + strlen(value) + 2);
      if (!environ[i]) {
         return -1; // Memory allocation failed
      }
      strcpy(environ[i], name);
      strcat(environ[i], "=");
      strcat(environ[i], value);
   }
   return 0;
}

