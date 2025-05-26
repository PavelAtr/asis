#include <mntent.h>

/* NOT REALIZED */

FILE file;
struct mntent mntret;

FILE *setmntent(const char *filename, const char *type)
{
   return &file;
}
struct mntent *getmntent(FILE *stream)
{
   return &mntret;
}

int addmntent(FILE* stream,
              const struct mntent* mnt)
{
   return 0;
}

int endmntent(FILE *streamp)
{
   return 0;
}

char *hasmntopt(const struct mntent *mnt, const char *opt)
{
   return "bad mnt opt";
}
