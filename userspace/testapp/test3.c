#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

int main(int argc, char** argv) {
   char* s1 = "/tinysys/bin/toybox sh";
   char* s2 = strrchr(s1, ' ');
   char* s3 = strrchr(s2, '/');

   printf("%s %d\n", s2, strlen(s2));
   printf("%s %d\n", s3, strlen(s3));
   return 0;
}
