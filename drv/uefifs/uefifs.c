#include "../../core/uefi/uefi.h"
#include "uefifs.h"

struct atimespec {
   long long     tv_sec;   /* Seconds */
   long long  tv_nsec;  /* Nanoseconds [0, 999'999'999] */
};

struct astat {
  unsigned int        st_mode;     /* File type and mode */
  unsigned int st_uid;      /* User ID of owner */
  unsigned int st_gid;      /* Group ID of owner */
  unsigned long long        st_size;
  int st_nlink;
  short st_major;
  short st_minor;
  unsigned long long st_dev;
  unsigned long long st_rdev;
  long long  st_ino;
  long long st_blksize;
  long long st_blocks;
  long long      st_atime;
  long long      st_mtime;
  long long      st_ctime;
  struct  atimespec st_atim;       /* time of last access */
  struct  atimespec st_mtim;       /* time of last data modification */
  struct  atimespec st_ctim;       /* time of last file status change */
  struct  atimespec st_birthtim;   /* time of file creation */
};


#define PATH_MAX 4096

char tmp[PATH_MAX];

char* calcpath(const char* path)
{
   memset(tmp, 0x0, PATH_MAX);
   strcpy(tmp, path);
   errno_t i;
   for (i = 0; tmp[i] != '\0'; i++)
      if (tmp[i] == '/') {
         tmp[i] = '\\';
      }
   return tmp;
}

errno_t uefifs_mknod(void* sbfs, const char *pathname, uid_t uid, gid_t gid,
   mode_t mode)
{
   return 0;
}

errno_t uefifs_modnod(void* sbfs, const char* pathname, uid_t uid, gid_t gid,
   mode_t mode)
{
   return 0;
}

errno_t uefifs_rmnod(void* sbfs, const char *pathname, uid_t curuid,
   gid_t curgid)
{
   return 0;
}

errno_t uefifs_truncate(void* sb, const char *pathname, len_t len)
{
   return 0;
}

errno_t uefifs_link(void* sb, const char* src, const char* dst, bool_t move,
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
   f = fopen(calcpath(path), mode);
}

len_t uefifs_fread(void* sbfs, const char* path, void* ptr, len_t size,
   len_t off)
{
   cachefile(path, "r");
   if (!f) {
      return 0;
   }
   fseek(f, off, SEEK_SET);
   len_t ret = fread(ptr, 1, size, f);
   return ret;
}

len_t uefifs_fwrite(void* sbfs, const char* path, const void* ptr, len_t size,
   len_t off)
{
   cachefile(path, "r+");
   if (!f) {
      return 0;
   }
   fseek(f, off, SEEK_SET);
   len_t ret = fwrite(ptr, 1, size, f);
   return ret;
}

errno_t uefifs_stat(void* sbfs, const char* path, void* statbuf)
{
   struct stat st;
   struct astat* tst = statbuf;
   char* pathname = calcpath(path);
   errno_t ret = stat(pathname, &st);
   tst->st_mode = st.st_mode;
   tst->st_size = st.st_size;
   if (strcmp(pathname, "\\dev\\tty") == 0) {
      tst->st_mode = (tst->st_mode & ~S_IFMT) | S_IFCHR;
      tst->st_major = 0;
      tst->st_minor = 5;
   }
   if (strcmp(pathname, "\\dev\\sda") == 0) {
      tst->st_mode = (tst->st_mode & ~S_IFMT) | S_IFBLK;
      tst->st_major = 8;
      tst->st_minor = 0;
   }
   if (strcmp(pathname, "\\dev\\fb0") == 0) {
      tst->st_mode = (tst->st_mode & ~S_IFMT) | S_IFCHR;
      tst->st_major = 29;
      tst->st_minor = 0;
   }
#ifndef UEFI
   tst->st_uid = st.st_uid;
   tst->st_gid = st.st_gid;
#endif
   return ret;
}

struct tinydirent uefi_tinydent;
void* uefifs_readdir(void* sbfs, const char* path, int ndx)
{
   char* pathname = calcpath(path);
   DIR* dir = opendir(pathname);
   if (!dir) {
      return NULL;
   }
   counter_t i;
   struct dirent* dent;
   for (i = 0; i <= (counter_t)ndx; i++) {
      dent = readdir(dir);
      if (dent && i == (counter_t)ndx) {
         strncpy(uefi_tinydent.d_name, dent->d_name, MAX_PATH_PART);
         closedir(dir);
         return &uefi_tinydent;
      }
   }
   closedir(dir);
   return NULL;
}

bool_t uefifs_can_read(void* sbfs, const char* path, uid_t uid, gid_t gid)
{
   return 1;
}

bool_t uefifs_can_write(void* sbfs, const char* path, uid_t uid, gid_t gid)
{
   return 1;
}

bool_t uefifs_can_execute(void* sbfs, const char* path, uid_t uid, gid_t gid)
{
   return 1;
}

errno_t  uefifs_mount(device* dev, mountpoint* mount, const char* options)
{
   mount->sbfs = NULL;
   mount->mount_mknod = &uefifs_mknod;
   mount->mount_modnod = &uefifs_modnod;
   mount->mount_rmnod = &uefifs_rmnod;
   mount->mount_link = &uefifs_link;
   mount->mount_truncate = &uefifs_truncate;
   mount->mount_stat =  &uefifs_stat;
   mount->mount_fread = &uefifs_fread;
   mount->mount_fwrite = &uefifs_fwrite;
   mount->mount_readdir = &uefifs_readdir;
   mount->mount_can_read = &uefifs_can_read;
   mount->mount_can_write = &uefifs_can_write;
   mount->mount_can_execute = &uefifs_can_execute;
   return 0;
}

mode_t uefifs2tiny_fmode(mode_t mode)
{
   return mode;
}


mode_t tiny2uefifs_fmode(mode_t mode)
{
   return mode;
}





