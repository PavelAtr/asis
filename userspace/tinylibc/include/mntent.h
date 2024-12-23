#ifndef _MNTENT_H
#define _MNTENT_H

struct mntent {
   char *mnt_fsname;   /* name of mounted filesystem */
   char *mnt_dir;      /* filesystem path prefix */
   char *mnt_type;     /* mount type (see mntent.h) */
   char *mnt_opts;     /* mount options (see mntent.h) */
   int   mnt_freq;     /* dump frequency in days */
   int   mnt_passno;   /* pass number on parallel fsck */
};

#endif