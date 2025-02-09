#include <byteswap.h>

uint32_t bswap_32(uint32_t x)
{
   char* t =(char*)&x;
   char c;
   c = t[0];
   t[0] = t[3];
   t[3] = c;
   c = t[1];
   t[1] = t[2];
   t[2] = c;
   return x;
}