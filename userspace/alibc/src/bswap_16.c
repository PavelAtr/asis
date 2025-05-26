#include <byteswap.h>

uint16_t bswap_16(uint16_t x)
{
   char* t =(char*)&x;
   char c;
   c = t[0];
   t[0] = t[1];
   t[2] = c;
   return x;
}
