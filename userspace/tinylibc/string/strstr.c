#include <string.h>

const char *strstr(const char *haystack, const char *needle)
{
   int i = 0;
   int j = 0;
   int ret = 0;
   char found = 0;
   while (haystack[i] != '\0') {
      if (needle[j] == '\0') {
         break;
      }
      if (haystack[i] == needle[j]) {
         if (j == 0) {
            found = 1;
            ret = i;
         }
         j++;
      } else {
         if (found) {
            i = ret + 1;
         }
         found = 0;
         j = 0;
      }
      i++;
   }
   if (found) {
      return &haystack[ret];
   } else {
      return NULL;
   }
}
