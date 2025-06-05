#include <asis.h>
#include "../../config.h"

#ifdef CONFIG_HOSTFS
#include "../../drv/hostfs/hostfs.h"
#endif

#ifdef CONFIG_UEFIFS
#include "../../drv/uefifs/uefifs.h"
#endif

#include <string.h>
#include <errno.h>
#include <sys/stat.h>

mountpoint mountpoints[MAXMOUNT];

mountpoint* sys_get_mountpoint(const char* file)
{
   size_t best = 0;
   mountpoint* ret = NULL;
   short i;
   if (!file) {
      return NULL;
   }
   for (i = 0; i < MAXMOUNT; i++)
      if (mountpoints[i].path) {
         if (strstr(file, mountpoints[i].path) == file) {
            size_t len = strlen(mountpoints[i].path);
            if (len > best) {
               best = len;
               ret = &mountpoints[i];
            }
         }
      }
   return ret;
}

const char* sys_calcpath(mountpoint* mount, const char* file)
{
   const char* mnt = (strcmp(mount->path, "/") == 0)? "" : mount->path;
   return &file[strlen(mnt)];
}

mountpoint* _get_free_mountpoint()
{
   int i;
   for (i = 0; i < MAXMOUNT; i++)
      if (!mountpoints[i].path) {
         return &mountpoints[i];
      }
   return NULL;
}

int  _sys_mount(device* dev, mountpoint* mount, const char* fstype,
   const char* options)
{
#ifdef CONFIG_HOSTFS
   if (strcmp(fstype, "hostfs") == 0) {
      return hostfs_mount(dev, mount, options);
   }
#endif

#ifdef CONFIG_UEFIFS
   if (strcmp(fstype, "uefifs") == 0) {
      return uefifs_mount(dev, mount, options);
   }
#endif

/*   if (strcmp(fstype, "weekfs") == 0) {
      return weekfs_mount(dev, mount, options);
   } GARBAGE*/
   current_errno = ENOTSUP;
   return -1;
}

int sys_mount(const char* blk, const char* dir, const char* fstype,
   const char* options)
{
   sys_printf(SYS_INFO "Mounting %s on %s type %s\n", blk, dir, fstype);
   mountpoint* mount = _get_free_mountpoint();
   device* dev = sys_get_device_byname(blk, S_IFBLK);
   if (!mount || !dev) {
      current_errno = ENOENT;
      return -1;
   }
   if (strcmp(dir, "/") == 0) {
      goto mount;
   }
   struct stat st;
   if (sys_stat(dir, &st)) {
      current_errno = ENOENT;
      return -1;
   }
   if (!(st.st_mode & S_IFDIR)) {
      current_errno = ENOTDIR;
      return -1;
   }
mount:
   int ret = _sys_mount(dev, mount, fstype, options);
   if (!ret) mount->path = dir;

   return ret;
}

int sys_umount(const char* dir)
{
   mountpoint* mount = sys_get_mountpoint(dir);
   sys_free(mount->sbfs);
   mount->sbfs = NULL;
   mount->path = NULL;
   return 0;
}


