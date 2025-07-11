#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <alloca.h>

char *mkdtemp(char *template)
{
   int suffixlen = 6;
   char* temp = alloca(strlen(template) + 8);
   char* suffix = &template[strlen(template) - suffixlen];
   int i;
   struct stat st;
   int fd = -1;
   for (i = 0; i <= 999999; i++) {
      strcpy(temp, template);
      snprintf(&temp[strlen(temp) - suffixlen], MAXSTRING, "%d", i);
      if (stat(temp, &st) == -1) {
         if (mkdir(temp, 0700) == -1) {
            return NULL;
         }
         strcpy(template, temp);
         break;
      }
   }
   return template;
}

