#include "../../config.h"
#include "hostfs.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

struct tinydirent {
  char           d_name[MAX_PATH_PART];
};

struct atimespec {
   long tv_sec;   /* Seconds */
   long tv_nsec;  /* Nanoseconds [0, 999'999'999] */
};

struct astat {
  unsigned int st_mode;     /* File type and mode */
  unsigned int st_uid;      /* User ID of owner */
  unsigned int st_gid;      /* Group ID of owner */
  unsigned long st_size;
  int st_nlink;
  short st_major;
  short st_minor;
  unsigned long st_dev;
  unsigned long st_rdev;
  long st_ino;
  long st_blksize;
  long st_blocks;
  long st_atime;
  long st_mtime;
  long st_ctime;
  struct  atimespec st_atim;       /* time of last access */
  struct  atimespec st_mtim;       /* time of last data modification */
  struct  atimespec st_ctim;       /* time of last file status change */
  struct  atimespec st_birthtim;   /* time of file creation */
};

#include <sys/stat.h>

errno_t hostfs_mknod(void* sbfs, const char *pathname, uid_t uid, gid_t gid,
   mode_t mode)
{
   mode_t devtype = mode & S_IFMT;
   const char* path = pathname;
   switch (devtype) {
   case S_IFBLK:
      return mknod(path, mode, 0);
   case S_IFCHR:
      return mknod(path, mode, 0);
   case S_IFDIR:
      return mkdir(path, mode);;
   case S_IFIFO:
      printf("Creating FIFO %s with mode %o\n", path, mode);
      return mkfifo(path, mode);
   case S_IFLNK:
      break;
   case S_IFREG:
      if (mode & S_IFREG) {
         FILE* f = fopen(path, "w");
         if (!f) {
            return ENOENT;
         }
         fclose(f);
         return 0;
      }
      break;
   case S_IFSOCK:
      break;
   default:
      break;
   }
   sys_printf(SYS_INFO "Unsupported mknod %s\n", pathname);
   return ENOTSUP;
}

errno_t hostfs_modnod(void* sbfs, const char* pathname, uid_t uid, gid_t gid,
   mode_t mode)
{
   return 0;
}

errno_t hostfs_rmnod(void* sbfs, const char *pathname, uid_t curuid,
   gid_t curgid)
{
   const char* path = pathname;
   if (unlink(path) < 0) {
      current_errno = EIO;
      return -1; // I/O error
   }
   return 0;
}

errno_t hostfs_truncate(void* sb, const char *pathname, len_t len)
{
   const char* path = pathname;
   return truncate(path, len);
}

errno_t hostfs_link(void* sb, const char* src, const char* dst, bool_t move,
   uid_t uid, gid_t gid)
{
   return 0;
}

FILE* f = NULL;
const char* cachepath = "";
const char* cachemode = "";

void cachefile(const char* path, const char* mode)
{
   if (strcmp(path, cachepath) == 0 && strcmp(mode, cachemode) == 0 && f) {
      return; // already cached
   }
   if (f) {
      fclose(f);
      f = NULL;
      cachepath = "";
      cachemode = "";
   }
   cachepath = path;
   cachemode = mode;
   f = fopen(path, mode);
}

len_t hostfs_fread(void* sbfs, const char* path, void* ptr, len_t size,
   len_t off)
{
   cachefile(path, "r");
   if (!f) {
      return 0;
   }
   fseek(f, off, SEEK_SET);
   return fread(ptr, 1, size, f);
}

len_t hostfs_fwrite(void* sbfs, const char* path, const void* ptr, len_t size,
   len_t off)
{
   cachefile(path, "r+");
   if (!f) {
      return 0;
   }
   fseek(f, off, SEEK_SET);
   return fwrite(ptr, 1, size, f);
}

errno_t hostfs_stat(void* sbfs, const char* pathname, void* statbuf)
{
   struct stat st;
   struct astat* tst = statbuf;
   errno_t ret = stat(pathname, &st);
   tst->st_mode = st.st_mode;
   tst->st_size = st.st_size;
   tst->st_uid = st.st_uid;
   tst->st_gid = st.st_gid;
   tst->st_major = 0;
   tst->st_minor = 0;
   return ret;
}

struct tinydirent tinydent;
void* hostfs_readdir(void* sbfs, const char* path, int ndx)
{
   DIR* dir = opendir(path);
   if (!dir) {
      return NULL;
   }
   counter_t i;
   struct dirent* dent;
   for (i = 0; i <= (counter_t)ndx; i++) {
      dent = readdir(dir);
      if (dent && i == (counter_t)ndx) {
         strncpy(tinydent.d_name, dent->d_name, MAX_PATH_PART);
         closedir(dir);
         return &tinydent;
      }
   }
   closedir(dir);
   return NULL;
}


bool_t hostfs_can_read(void* sbfs, const char* path, uid_t uid, gid_t gid)
{
   return 1;
}

bool_t hostfs_can_write(void* sbfs, const char* path, uid_t uid, gid_t gid)
{
   return 1;
}

bool_t hostfs_can_execute(void* sbfs, const char* path, uid_t uid, gid_t gid)
{
   return 1;
}

errno_t  hostfs_mount(device* dev, mountpoint* mount, const char* options)
{
   mount->sbfs = NULL;
   mount->mount_mknod = &hostfs_mknod;
   mount->mount_modnod = &hostfs_modnod;
   mount->mount_rmnod = &hostfs_rmnod;
   mount->mount_link = &hostfs_link;
   mount->mount_truncate = &hostfs_truncate;
   mount->mount_stat =  &hostfs_stat;
   mount->mount_fread = &hostfs_fread;
   mount->mount_fwrite = &hostfs_fwrite;
   mount->mount_readdir = &hostfs_readdir;
   mount->mount_can_read = &hostfs_can_read;
   mount->mount_can_write = &hostfs_can_write;
   mount->mount_can_execute = &hostfs_can_execute;
   return 0;
}
