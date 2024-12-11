#include <grp.h>

void setgrent(void)
{
   endgrent();
   dbgroup = fopen(GROUP_FILE, "r");
}

void endgrent(void)
{
   if (dbgroup) {
      fclose(dbgroup);
      dbgroup = NULL;
   }
}
