char* chars = "0123456789abcdef";
short itoa_len(long num, short base)
{
   long tmp = num;
   short i = 0;
   if (tmp < 0) {
      tmp = -tmp;
   }
   unsigned char digit = tmp % base;
   i++;
   while ((tmp = tmp/base) != 0) {
      digit = tmp % base;
      i++;
   }
   if (num < 0) {
      i++;
   }
   return i;
}

short itoa(long num, short base, char* buf)
{
   long tmp = num;
   short len = itoa_len(num, base);
   short i = len - 1;
   if (!buf) {
      return len;
   }
   if (tmp < 0) {
      tmp = -tmp;
   }
   unsigned char digit = tmp % base;
   buf[i] = chars[digit];
   i--;
   while ((tmp = tmp/base) != 0) {
      digit = tmp % base;
      buf[i] = chars[digit];
      i--;
   }
   if (num < 0) {
      buf[i] = '-';
   }
   buf[len] = '\0';
   return len;
}
