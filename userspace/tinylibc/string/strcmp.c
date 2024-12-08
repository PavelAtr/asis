int strcmp(const char *s1, const char *s2)
{
   int i = 0;
   int equal = 1;
   for(i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
      if (s1[i] != s2[i]) {
         equal = 0;
      }
   if (equal && s1[i] == '\0' && s2[i] == '\0') {
      return 0;
   }
   if (s1[i] == '\0') {
      return -1;
   }
   if (s2[i] == '\0') {
      return 1;
   }
   return 1;
}
