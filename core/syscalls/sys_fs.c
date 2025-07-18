/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <sys/stat.h>
#include <asis.h>
#include <sys/capability.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

len_t sys_afread(const char* path, void* ptr, len_t size, len_t off)
{
   mountpoint* mount;
   const char* file = sys_calcpath(&mount, path);
   if (!mount) {
      return 0;
   }
   
   if (!mount->mount_can_read(mount->sbfs, file, current->uid, current->gid)) {
      return 0;
   }
   device* dev;
   struct stat st;
   if (mount->mount_stat(mount->sbfs, file, &st)) {
      return 0;
   }
   mode_t devtype = st.st_mode & S_IFMT;

   switch (devtype) {
   case S_IFBLK:
   case S_IFCHR:
      if ((dev = sys_get_device_byname(path, devtype))) {
         dev->dev_seek(dev->devparams, off);
         return dev->dev_read(dev->devparams, ptr, size);
      }
      break;
   case S_IFDIR:
      break;
   case S_IFIFO:
      break;
   case S_IFLNK:
      break;
   case S_IFREG:
      return mount->mount_fread(mount->sbfs, file, ptr, size, off);
      break;
   case S_IFSOCK:
      break;
   default:
      break;
   }
   return 0;
}

len_t sys_afwrite(const char* path, const void* ptr, len_t size, len_t off)
{
   mountpoint* mount;
   const char* file = sys_calcpath(&mount, path);
   if (!mount) {
      return 0;
   }
   
   if (!mount->mount_can_write(mount->sbfs, file, current->uid, current->gid)) {
      return 0;
   }
   device* dev;
   struct stat st;
   if (mount->mount_stat(mount->sbfs, file, &st)) {
      return 0;
   }
   mode_t devtype = st.st_mode & S_IFMT;
   switch (devtype) {
   case S_IFBLK:
   case S_IFCHR:
      if ((dev = sys_get_device_byname(path, devtype))) {
         dev->dev_seek(dev->devparams, off);
         return dev->dev_write(dev->devparams, ptr, size);
      }
      break;
   case S_IFDIR:
      break;
   case S_IFIFO:
      break;
   case S_IFLNK:
      break;
   case S_IFREG:
      return mount->mount_fwrite(mount->sbfs, file, ptr, size, off);
      break;
   case S_IFSOCK:
      break;
   default:
      break;
   }
   return 0;
}

errno_t sys_ioctl(const char* path, ulong_t request, void* arg1, void* arg2,  void* arg3, void* arg4)
{
   mountpoint* mount;
   const char* file = sys_calcpath(&mount, path);
   if (!mount) {
      return ENOENT;
   }
   
   if (!mount->mount_can_write(mount->sbfs, file, current->uid, current->gid)) {
      return EPERM;
   }
   device* dev;
   struct stat st;
   if (mount->mount_stat(mount->sbfs, file, &st)) {
      return ENOENT;
   }
   mode_t devtype = st.st_mode & S_IFMT;
   switch (devtype) {
   case S_IFBLK:
      if ((dev = sys_get_device_byname(path, devtype))) {
         return dev->dev_ioctl(dev->devparams, request, arg1, arg2, arg3, arg4);
      }
      break;
   case S_IFCHR:
      if ((dev = sys_get_device_byname(path, devtype))) {
         return dev->dev_ioctl(dev->devparams, request, arg1, arg2, arg3, arg4);
      }
      break;
   case S_IFDIR:
      break;
   case S_IFIFO:
      break;
   case S_IFLNK:
      break;
   case S_IFREG:
      break;
   case S_IFSOCK:
      break;
   default:
      break;
   }
   sys_printf(SYS_INFO "Unsupported ioctl %ld\n", request);
   return ENOTSUP;
}

errno_t sys_stat(const char* pathname, void* statbuf)
{
   mountpoint* mount;
   const char* path = sys_calcpath(&mount, pathname);
   if (!mount) {
      return ENOENT;
   }
   int_t err;
   if ((err = mount->mount_stat(mount->sbfs, path, statbuf))) {
      return err;
   }
   return 0;
}


errno_t sys_mknod(const char* pathname, mode_t mode)
{
   mountpoint* mount;
   const char* path = sys_calcpath(&mount, pathname);
   if (!mount) {
      return ENOENT;
   }
   errno_t err;
   if ((err = mount->mount_mknod(mount->sbfs, path, current->uid, current->gid, mode))) {
      return err;
   }
   return 0;
}

#define is_owner_or_capable(cap) (security->capable(cap) || st.st_uid == current->uid)

errno_t sys_modnod(const char* pathname, uid_t uid, gid_t gid, mode_t mode)
{
   mountpoint* mount;
   const char* path = sys_calcpath(&mount, pathname);
   if (!mount) {
      return ENOENT;
   }
   
   struct stat st;
   if (mount->mount_stat(mount->sbfs, path, &st)) {
      return ENOENT;
   }
   mode_t newmode = (st.st_mode & S_IFMT) | mode;
   if (!(st.st_mode == newmode)) {
      if (!is_owner_or_capable(CAP_FOWNER)) {
         return EPERM;
      }
      if (!is_owner_or_capable(CAP_FSETID)) {
         newmode &= ~S_ISUID;
         newmode &= ~S_ISGID;
      }
   }
   if (!(st.st_uid == uid)) {
      if (!is_owner_or_capable(CAP_CHOWN)) {
         return EPERM;
      }
      if (!is_owner_or_capable(CAP_FSETID)) {
         mode &= ~S_ISUID;
      }
   }
   if (!(st.st_gid == gid)) {
      if (!is_owner_or_capable(CAP_CHOWN)) {
         return EPERM;
      }
      if (!is_owner_or_capable(CAP_FSETID)) {
         mode &= ~S_ISGID;
      }
   }
   errno_t err;
   if ((err = mount->mount_modnod(mount->sbfs, path, uid, gid, newmode))) {
      return err;
   }
   return 0;
}

errno_t sys_unlink(const char *pathname)
{
   mountpoint* mount;
   const char* path = sys_calcpath(&mount, pathname);
   if (!mount) {
      return ENOENT;
   }
   errno_t err ;
   if ((err = mount->mount_rmnod(mount->sbfs, path, current->uid, current->gid))) {
      return err;
   }
   return 0;
}

errno_t sys_link(const char *oldpath, const char *newpath, bool_t move)
{
   mountpoint* mount1;
   const char* oldpath_calc = sys_calcpath(&mount1, oldpath);
   mountpoint* mount2;
   const char* newpath_calc = sys_calcpath(&mount2, newpath);
   if (mount1 != mount2) {
      return ENOTSUP;
   }
   errno_t err;
   if ((err = mount1->mount_link(mount1->sbfs, oldpath_calc, newpath_calc,
         move, current->uid, current->gid))) {
      return err;
   }
   return 0;
}

void* sys_readdir(char* pathname, int_t ndx)
{
   mountpoint* mount;
   const char* file = sys_calcpath(&mount, pathname);
   if (!mount) {
      return NULL;
   }
   
   if (!mount->mount_can_read(mount->sbfs, file, current->uid, current->gid)) {
      return 0;
   }
   return mount->mount_readdir(mount->sbfs, file, ndx);
}

errno_t sys_truncate(const char *pathname, size_t length)
{
   mountpoint* mount;
   const char* path = sys_calcpath(&mount, pathname);
   if (!mount) {
      return ENOENT;
   }
   errno_t err;
   if ((err = mount->mount_truncate(mount->sbfs, path, length))) {
      return err;
   }
   return 0;
}

errno_t sys_chdir(char* pathname) {
   struct stat st;
   mountpoint* mount = sys_get_mountpoint(pathname);
   if (!mount) {
      return ENOENT;
   }
   const char* mnt = (strcmp(mount->path, "/") == 0)? "" : mount->path;
   const char* path = &pathname[strlen(mnt)];
   errno_t err;
   if ((err = mount->mount_stat(mount->sbfs, path, &st))) {
      sys_printf(SYS_ERROR "sys_chdir: mount_stat failed for %s\n", path);
      goto fail;
   }
   if (!S_ISDIR(st.st_mode)) {
      sys_printf(SYS_ERROR "sys_chdir: %s is not a directory\n", path);
      err = ENOTDIR;
      goto fail;
   }
   if (!mount->mount_can_execute(mount->sbfs, path, current->uid, current->gid)
      && !security->capable(CAP_DAC_READ_SEARCH)) {
         sys_printf(SYS_ERROR "sys_chdir: permission denied for %s\n", path);
         err = EACCES;
         goto fail;
   }
end:
   sys_free(current->cwd);
   current->cwd = strdup(path);
   err = 0;
fail:
   return err;
}

char* get_current_dir_name(void)
{
   return strdup(current->cwd);
}

