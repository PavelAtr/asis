#include <byteswap.h>

uint64_t bswap_64(uint64_t x)
{
   char* t =(char*)&x;
   char c;
   c = t[0];
   t[0] = t[7];
   t[7] = c;
   c = t[1];
   t[1] = t[6];
   t[6] = c;
   c = t[2];
   t[2] = t[5];
   t[5] = c;
   c = t[3];
   t[3] = t[4];
   t[4] = c;
   return x;
}