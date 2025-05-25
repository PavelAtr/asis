#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H

           struct statfs {
               unsigned long f_type;    /* Type of filesystem (see below) */
               unsigned long f_bsize;   /* Optimal transfer block size */
               unsigned long f_blocks;  /* Total data blocks in filesystem */
               unsigned long f_bfree;   /* Free blocks in filesystem */
               unsigned long f_bavail;  /* Free blocks available to
                                        unprivileged user */
               unsigned long f_files;   /* Total inodes in filesystem */
               unsigned long f_ffree;   /* Free inodes in filesystem */
               unsigned long f_fsid;    /* Filesystem ID */
               unsigned long f_namelen; /* Maximum length of filenames */
               unsigned long f_frsize;  /* Fragment size (since Linux 2.6) */
               unsigned long f_flags;   /* Mount flags of filesystem
                                        (since Linux 2.6.36) */
               unsigned long f_spare[4];
                               /* Padding bytes reserved for future use */
           };

int statfs(const char *path, struct statfs *buf);
int fstatfs(int fd, struct statfs *buf);

#endif
