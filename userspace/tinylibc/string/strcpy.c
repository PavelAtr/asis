char* strcpy(char* dst, const char* src)
{
   int i;
   for (i = 0; src[i] != '\0'; i++) {
      dst[i] = src[i];
   }
   dst[i] = src[i];
   return dst;
}