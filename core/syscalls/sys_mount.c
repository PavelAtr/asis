/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

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

char ret[1024];

char* fullpath(const char* dir, const char* path)
{
   if (!dir || !path) {
      return NULL;
   }
   if (path[0] == '/') {
      if (strstr(path, "/dev/") == path) {
         strcpy(ret, path);
         ret[strlen(path)] = '\0';
         goto end;
      }
      path++; // Skip the leading slash
   }
   size_t cwdlen = strlen(dir);
   size_t pathlen = strlen(path);
   strcpy(ret, dir);
   if (path == NULL || path[0] == '\0') {
      ret[cwdlen] = '\0';
      goto end;
   }
	   strcpy(ret + cwdlen, path);
      ret[cwdlen + pathlen] = '\0';
end:
   sys_printf(SYS_DEBUG "Fullpath: %s\n", ret);
   return ret;
}

const char* sys_calcpath(mountpoint** mount, const char* path)
{
   char* file = fullpath(current->cwd, path);
   if (!file) {
      *mount = NULL;
      return NULL;
   }  
   *mount = sys_get_mountpoint(file);
   const char* mnt = (strcmp((*mount)->path, "/") == 0)? "" : (*mount)->path;
   
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

errno_t  _sys_mount(device* dev, mountpoint* mount, const char* fstype,
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
   return ENOTSUP;
}

errno_t sys_mount(const char* blk, const char* dir, const char* fstype,
   const char* options)
{
   sys_printf(SYS_INFO "Mounting %s on %s type %s\n", blk, dir, fstype);
   mountpoint* mount = _get_free_mountpoint();
   device* dev = sys_get_device_byname(blk, S_IFBLK);
   if (!mount || !dev) {
      return ENOENT;
   }
   if (strcmp(dir, "/") == 0) {
      goto mount;
   }
   struct stat st;
   errno_t err;
   if ((err = sys_stat(dir, &st))) {
      return err;
   }
   if (!(st.st_mode & S_IFDIR)) {
      return ENOTDIR;
   }
mount:
   errno_t ret = _sys_mount(dev, mount, fstype, options);
   if (!ret) mount->path = dir;

   return ret;
}

errno_t sys_umount(const char* dir)
{
   sys_printf(SYS_INFO "Umounting %s\n", dir);
   mountpoint* mount = sys_get_mountpoint(dir);
   mount->mount_umount(mount->sbfs);
   sys_free(mount->sbfs);
   mount->sbfs = NULL;
   mount->path = NULL;
   return 0;
}


