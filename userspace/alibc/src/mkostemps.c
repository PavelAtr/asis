#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int mkostemps(char *template, int suffixlen, int flags)
{
   char* temp = malloc(strlen(template) + 8);
   char* suffix = &template[strlen(template) - suffixlen];
   int i;
   struct stat st;
   int fd = -1;
   for (i = 0; i <= 999999; i++) {
      strcpy(temp, template);
      snprintf(&temp[strlen(temp) - suffixlen], MAXSTRING, "%d%s", i, suffix);
      if (stat(temp, &st) == -1) {
         fd = open(temp, O_CREAT | flags, 0600);
         strcpy(template, temp);
         break;
      }
   }
   free(temp);
   return fd;
}

int mkstemp(char *template)
{
   return mkostemps(template, 0, O_RDWR);
}

int mkostemp(char *template, int flags)
{
   return mkostemps(template, 0, flags);
}

int mkstemps(char *template, int suffixlen)
{
   return mkostemps(template, suffixlen, O_RDWR);
}
