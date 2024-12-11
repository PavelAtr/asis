#include <grp.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int fgetgrent_r(FILE* stream, struct group* gbuf,
                 char* buf, size_t buflen,
                 struct group** gbufp)
{
   memset(buf, 0x0, buflen);
   if (!fgets(buf, buflen, stream)) {
      *gbufp = NULL;
      return ERANGE;
   }
   buf[strlen(buf) - 1] = '\0';
   gbuf->gr_name = strtok(buf, ":");
   gbuf->gr_passwd = strtok(NULL, ":");
   gbuf->gr_gid = atoi(strtok(NULL, ":"));
   char* temp = strtok(NULL, ":");
   int i;
   int numtok = 0;
   for (i = 0; i < strlen(temp); i++) {
      numtok = (temp[i] == ',')? numtok + 1: numtok; 
   }
   gbuf->gr_mem = malloc(sizeof(char*) * (numtok + 1));
   i = 0;
   gbuf->gr_mem[i++] = strtok(temp, ",");
   char* tok;
   while ((tok = strtok(NULL, ","))) {
      gbuf->gr_mem[i++] = tok;
   }
   gbuf->gr_mem[i] = NULL;
   *gbufp = gbuf;
   return 0;
}
