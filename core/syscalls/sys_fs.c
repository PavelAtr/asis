#include <sys/stat.h>
#include <asis.h>
#include <sys/capability.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

len_t sys_afread(const char* path, void* ptr, len_t size, len_t off)
{
   mountpoint* mount = sys_get_mountpoint(path);
   if (!mount) {
      current->sys_errno = ENOENT;
      return 0;
   }
   const char* file = sys_calcpath(mount, path);
   if (!mount->mount_can_read(mount->sbfs, file, current->uid, current->gid)) {
      current->sys_errno = EPERM;
      return 0;
   }
   device* dev;
   struct tinystat st;
   if (mount->mount_stat(mount->sbfs, file, &st)) {
      current->sys_errno = ENOENT;
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
   mountpoint* mount = sys_get_mountpoint(path);
   if (!mount) {
      current->sys_errno = ENOENT;
      return 0;
   }
   const char* file = sys_calcpath(mount, path);
   if (!mount->mount_can_write(mount->sbfs, file, current->uid, current->gid)) {
      current->sys_errno = EPERM;
      return 0;
   }
   device* dev;
   struct tinystat st;
   if (mount->mount_stat(mount->sbfs, file, &st)) {
      current->sys_errno = ENOENT;
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

errno_t sys_ioctl(const char* path, ulong_t request, va_list* vl)
{
   mountpoint* mount = sys_get_mountpoint(path);
   if (!mount) {
      current->sys_errno = ENOENT;
      return 0;
   }
   const char* file = sys_calcpath(mount, path);
   if (!mount->mount_can_write(mount->sbfs, file, current->uid, current->gid)) {
      current->sys_errno = EPERM;
      return 0;
   }
   device* dev;
   struct tinystat st;
   if (mount->mount_stat(mount->sbfs, file, &st)) {
      current->sys_errno = ENOENT;
      return 0;
   }
   mode_t devtype = st.st_mode & S_IFMT;
   switch (devtype) {
   case S_IFBLK:
      if ((dev = sys_get_device_byname(path, devtype))) {
         return dev->dev_ioctl(dev->devparams, request, *vl);
      }
      break;
   case S_IFCHR:
      if ((dev = sys_get_device_byname(path, devtype))) {
         return dev->dev_ioctl(dev->devparams, request, *vl);
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

int_t sys_stat(const char* pathname, void* statbuf)
{
   mountpoint* mount= sys_get_mountpoint(pathname);
   if (!mount) {
      current->sys_errno = ENOENT;
      return -1;
   }
   int_t err = mount->mount_stat(mount->sbfs, sys_calcpath(mount, pathname),
         statbuf);
   if (err) {
      current->sys_errno = ENOENT;
      return -1;
   }
   return 0;
}

int_t sys_mknod(const char* pathname, mode_t mode)
{
   mountpoint* mount= sys_get_mountpoint(pathname);
   if (!mount) {
      current->sys_errno = ENOENT;
      return -1;
   }
   errno_t err = mount->mount_mknod(mount->sbfs, sys_calcpath(mount, pathname),
         current->uid, current->gid, mode);
   if (err) {
      current->sys_errno = err;
      return -1;
   }
   return 0;
}

#define is_owner_or_capable(cap) (security->capable(cap) || st.st_uid == current->uid)

int_t sys_modnod(const char* pathname, uid_t uid, gid_t gid, mode_t mode)
{
   mountpoint* mount= sys_get_mountpoint(pathname);
   if (!mount) {
      current->sys_errno = ENOENT;
      return -1;
   }
   const char* path = sys_calcpath(mount, pathname);
   struct stat st;
   if (mount->mount_stat(mount->sbfs, path, &st)) {
      current->sys_errno = ENOENT;
      return -1;
   }
   mode_t newmode = (st.st_mode & S_IFMT) | mode;
   if (!(st.st_mode == newmode)) {
      if (!is_owner_or_capable(CAP_FOWNER)) {
         current->sys_errno = EPERM;
         return -1;
      }
      if (!is_owner_or_capable(CAP_FSETID)) {
         newmode &= ~S_ISUID;
         newmode &= ~S_ISGID;
      }
   }
   if (!(st.st_uid == uid)) {
      if (!is_owner_or_capable(CAP_CHOWN)) {
         current->sys_errno = EPERM;
         return -1;
      }
      if (!is_owner_or_capable(CAP_FSETID)) {
         mode &= ~S_ISUID;
      }
   }
   if (!(st.st_gid == gid)) {
      if (!is_owner_or_capable(CAP_CHOWN)) {
         current->sys_errno = EPERM;
         return -1;
      }
      if (!is_owner_or_capable(CAP_FSETID)) {
         mode &= ~S_ISGID;
      }
   }
   errno_t err = mount->mount_modnod(mount->sbfs, path, uid, gid, newmode);
   if (err) {
      current->sys_errno = err;
      return -1;
   }
   return 0;
}

int_t sys_unlink(const char *pathname)
{
   mountpoint* mount= sys_get_mountpoint(pathname);
   if (!mount) {
      current->sys_errno = ENOENT;
      return -1;
   }
   errno_t err = mount->mount_rmnod(mount->sbfs, sys_calcpath(mount, pathname),
         current->uid, current->gid);
   if (err) {
      current->sys_errno = err;
      return -1;
   }
   return 0;
}

int_t sys_link(const char *oldpath, const char *newpath, bool_t move)
{
   mountpoint* mount1= sys_get_mountpoint(oldpath);
   mountpoint* mount2= sys_get_mountpoint(newpath);
   if (mount1 != mount2) {
      current->sys_errno = ENOTSUP;
      return -1;
   }
   errno_t err = mount1->mount_link(mount1->sbfs, sys_calcpath(mount1, oldpath),
         sys_calcpath(mount2, newpath), move, current->uid, current->gid);
   if (err) {
      current->sys_errno = err;
      return -1;
   }
   return 0;
}

void* sys_readdir(char* pathname, int_t ndx)
{
   mountpoint* mount= sys_get_mountpoint(pathname);
   if (!mount) {
      current->sys_errno = ENOENT;
      return NULL;
   }
   const char* file = sys_calcpath(mount, pathname);
   if (!mount->mount_can_read(mount->sbfs, file, current->uid, current->gid)) {
      current->sys_errno = EPERM;
      return 0;
   }
   return mount->mount_readdir(mount->sbfs, file, ndx);
}

int_t sys_truncate(const char *pathname, size_t length)
{
   mountpoint* mount= sys_get_mountpoint(pathname);
   if (!mount) {
      current->sys_errno = ENOENT;
      return -1;
   }
   errno_t err = mount->mount_truncate(mount->sbfs, sys_calcpath(mount, pathname),
         length);
   if (err) {
      current->sys_errno = err;
      return -1;
   }
   return 0;
}


