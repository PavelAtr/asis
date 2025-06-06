#include <stdio.h>

char *fgets(char* s, int size, FILE* stream)
{
INIT_FDS
   int i;
   int c;
   for (i = 0; i < size - 1; i++) {
      c = getc(stream);
      s[i] = c;
      #ifdef UEFI_KERNEL
      if (c == '\r') {
         s[i] = '\n';
         break;      }
      #else
      if (c == '\n') {
         break;
      }
      #endif
      if (c == EOF) {
         break;
      }
      if (feof(stream)) {
         return NULL;
      }
      #ifdef UEFI_KERNEL
      if (stream == stdin) {   
         putchar(c);
      }
      #endif
   }
   s[i + 1] = '\0';
   return s;
}
