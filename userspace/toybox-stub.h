
struct statfs {
  long f_type;    /* Type of filesystem (see below) */
  long f_bsize;   /* Optimal transfer block size */
  long f_blocks;  /* Total data blocks in filesystem */
  long f_bfree;   /* Free blocks in filesystem */
  long f_bavail;  /* Free blocks available to
                        unprivileged user */
  long f_files;   /* Total inodes in filesystem */
  long f_ffree;   /* Free inodes in filesystem */
  long f_fsid;    /* Filesystem ID */
  long f_namelen; /* Maximum length of filenames */
  long f_frsize;  /* Fragment size (since Linux 2.6) */
  long f_flags;   /* Mount flags of filesystem
                        (since Linux 2.6.36) */
  long f_spare[4];
               /* Padding bytes reserved for future use */
};
