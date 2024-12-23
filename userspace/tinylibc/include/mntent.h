#ifndef _MNTENT_H
#define _MNTENT_H

#include <stdio.h>

struct mntent {
   char *mnt_fsname;   /* name of mounted filesystem */
   char *mnt_dir;      /* filesystem path prefix */
   char *mnt_type;     /* mount type (see mntent.h) */
   char *mnt_opts;     /* mount options (see mntent.h) */
   int   mnt_freq;     /* dump frequency in days */
   int   mnt_passno;   /* pass number on parallel fsck */
};

FILE *setmntent(const char *filename, const char *type);
struct mntent *getmntent(FILE *stream);
int addmntent(FILE* stream, const struct mntent* mnt);
int endmntent(FILE *streamp);
char *hasmntopt(const struct mntent *mnt, const char *opt);

#endif