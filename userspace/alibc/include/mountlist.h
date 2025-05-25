#include <sys/types.h>

struct mount_entry
{
  char *me_devname;             /* Device node name, including "/dev/". */
  char *me_mountdir;            /* Mount point directory name. */
  char *me_mntroot;             /* Directory on filesystem of device used */
                                /* as root for the (bind) mount. */
  char *me_type;                /* "nfs", "4.2", etc. */
  dev_t me_dev;                 /* Device number of me_mountdir. */
  struct mount_entry *me_next;
};

struct mount_entry *read_file_system_list (unsigned char need_fs_type);
void free_mount_entry (struct mount_entry *entry);
