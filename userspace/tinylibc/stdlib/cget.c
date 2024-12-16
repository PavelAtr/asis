#include <string.h>

/* NOT REALIZED */

int cgetent (char **buf, char **db_array, const char *name)
{
   return 0;
}

int cgetset (const char *ent)
{
   return 0;
}

int cgetmatch(const char *buf, const char *name)
{
   if (strstr(buf, name)) {
      return 0;
   }
   return -1;
}

char * cgetcap (char *buf, const char *cap, int type)
{
   return NULL;
}

int cgetnum (char *buf, const char *cap, long *num)
{
   return 0;
}

int cgetstr (char *buf, const char *cap, char **str)
{
   return 0;
}

int cgetustr (char *buf, const char *cap, char **str)
{
   return 0;
}

int cgetfirst (char **buf, char **db_array)
{
   return 0;
}

int cgetnext (char **buf, char **db_array)
{
   return 0;
}

int cgetclose (void)
{
   return 0;
}


