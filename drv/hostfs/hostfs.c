#include "../../config.h"
#include "hostfs.h"

#ifdef CONFIG_UEFI
#include "../../core/uefi/uefi.h"
#endif

#ifdef CONFIG_LINUX
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#endif

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

#ifdef CONFIG_LINUX
#include <sys/stat.h>
#endif

typedef struct {
   char name[512];
   uid_t uid;
   gid_t gid;
   mode_t mode;
} meta_t;

typedef struct {
   FILE* file;
   char* path;
   char* mode;
   char lock;
} cache_file;

#define MAXCACHE 20
int cache_index = -1;
cache_file cache[MAXCACHE];

FILE* get_cache(const char* path, const char* mode)
{
   int start = cache_index;
   int i;
   for (i = 0; i < MAXCACHE; i++)
   {
      if (cache[i].path && cache[i].mode) {
         if (strcmp(cache[i].mode, mode) == 0
            && strcmp(cache[i].path, path) == 0
            && !cache[i].lock)
         {
            cache[i].lock = 1;
            return cache[i].file;
         }
      }
   }
   while (1) {
      cache_index++;
      if (cache_index >= MAXCACHE)
         cache_index = -1;
      if (cache_index == start)
         return NULL;
      if (cache[cache_index].lock)
         continue;
      break;
   }
   printf("hostfs: cache_index = %d\n", cache_index);
   if (cache[cache_index].file) {
      fclose(cache[cache_index].file);
      free(cache[cache_index].path);
      free(cache[cache_index].mode);
   }
   cache[cache_index].file = fopen(path, mode);
   cache[cache_index].path = strdup(path);
   cache[cache_index].mode = strdup(mode);
   cache[cache_index].lock = 1;
   return cache[cache_index].file;
}

void end_cache(FILE* stream) {
   int i;
   for (i = 0; i < MAXCACHE; i++)
   {
      if (cache[i].file == stream)
      {
         cache[i].lock = 0;
         return;
      }
   }
}

void close_cache() {
   int i;
   for (i = 0; i < MAXCACHE; i++)
   {
      if (cache[i].file)
      {
         fclose(cache[i].file);
         free(cache[i].path);
         free(cache[i].mode);
      }
   }
}

FILE* fmeta = NULL;

char* calc_path(char* fullpath, void* sbfs, const char* path)
{
   hostfs_sbfs* hsbfs = (hostfs_sbfs*)sbfs;
   if (hsbfs->chroot && hsbfs->chroot[0] != '\0') {
      sprintf(fullpath, "%s%s", hsbfs->chroot, path);
      return fullpath;
   }
   sprintf(fullpath, "%s", path);
   #ifdef CONFIG_UEFI
   int i;
   for (i = 0; fullpath[i] != '\0'; i++)
   if (fullpath[i] == '/') {
      fullpath[i] = '\\';
   }
   #endif
   return fullpath; // If no chroot, return the path as is
}

meta_t* hostfs_get_meta(const char* path, meta_t* inmeta)
{
   if (!fmeta) {
      fmeta = fopen("meta", "r+");
      if (!fmeta) {
         printf("%s\n", "Error opening metadata file");
         return NULL;
      }
   }
   meta_t* meta = inmeta;
   if (fseek(fmeta, 0, SEEK_SET) < 0) {
      return NULL;
   }
   while (fread(meta, sizeof(meta_t), 1, fmeta) == 1) {
      if (strcmp(meta->name, path) == 0) {
         return meta;
      }
   }
   return NULL;
}

int hostfs_set_meta(const char* path, uid_t uid, gid_t gid, mode_t mode)
{
   meta_t meta;
   strncpy(meta.name, path, sizeof(meta.name) - 1);
   meta.name[sizeof(meta.name) - 1] = '\0';
   meta.uid = uid;
   meta.gid = gid;
   meta.mode = mode;

   if (!fmeta) {
      fmeta = fopen("meta", "r+");
      if (!fmeta) {
         printf("%s\n", "Error opening metadata file");
         return -1; // Error opening metadata file
      }
   }
   meta_t existing_meta;
   if (hostfs_get_meta(path, &existing_meta)) {
      // If the metadata already exists, we can update it
      if (fseek(fmeta, -((long)sizeof(meta_t)), SEEK_CUR) < 0) {
         return -1; // Error seeking in file
      }
   } else {
      // If it doesn't exist, we will append it
      if (fseek(fmeta, 0, SEEK_END) < 0) {
         return -1; // Error seeking in file
      }
   }
   if (fwrite(&meta, sizeof(meta_t), 1, fmeta) != 1) {
      return -1; // Error writing to file
   }
   fflush(fmeta);
   return 0; // Success
}

errno_t hostfs_mknod(void* sbfs, const char *pathname, uid_t uid, gid_t gid,
   mode_t mode)
{
   mode_t devtype = mode & S_IFMT;
   char fullpath[1024];
   const char* path = calc_path(fullpath, sbfs, pathname);
   printf("hostfs_mknod: %s, mode: %o\n", path, mode);
   hostfs_set_meta(pathname, uid, gid, mode);
   if (devtype == S_IFDIR)
   {
       mkdir(path, 0770);
       return 0;
   }
   FILE* f = fopen(path, "w");
   if (!f) {
      return ENOENT;
   }
   fclose(f);
   return 0;
}

errno_t hostfs_modnod(void* sbfs, const char* pathname, uid_t uid, gid_t gid,
   mode_t mode)
{
   return 0;
}

errno_t hostfs_rmnod(void* sbfs, const char *pathname, uid_t curuid,
   gid_t curgid)
{
   char fullpath[1024];
   const char* path = calc_path(fullpath, sbfs, pathname);
   if (unlink(path) < 0) {
      return EIO; // I/O error
   }
   return 0;
}

errno_t hostfs_truncate(void* sb, const char *pathname, len_t len)
{
   char fullpath[1024];
   const char* path = calc_path(fullpath, sb, pathname);
   #ifdef CONFIG_LINUX
      return truncate(path, len);
   #endif
   #ifdef CONFIG_UEFI
      return 0;
   #endif
}

errno_t hostfs_link(void* sb, const char* src, const char* dst, bool_t move,
   uid_t uid, gid_t gid)
{
   return 0;
}


len_t hostfs_fread(void* sbfs, const char* path, void* ptr, len_t size,
   len_t off)
{
   char fullpath[1024];
   char* file = calc_path(fullpath, sbfs, path);
   FILE* f = get_cache(file, "r");
   if (!f) {
      return 0;
   }
   fseek(f, off, SEEK_SET);
   size_t ret = fread(ptr, 1, size, f);
   end_cache(f);
   return ret;
}

len_t hostfs_fwrite(void* sbfs, const char* path, const void* ptr, len_t size,
   len_t off)
{
   char fullpath[1024];
   char* file = calc_path(fullpath, sbfs, path);
   FILE* f = get_cache(file, "r+");
   if (!f) {
      return 0;
   }
   fseek(f, off, SEEK_SET);
   size_t ret = fwrite(ptr, 1, size, f);
   end_cache(f);
   return ret;
}

errno_t hostfs_stat(void* sbfs, const char* path, void* statbuf)
{
   meta_t meta;
   struct stat st;
   struct astat* tst = statbuf;
   char fullpath[1024];
   char* pathname = calc_path(fullpath, sbfs, path);
   errno_t ret = stat(pathname, &st);
   if (ret == -1) {
      return ENOENT; // Error occurred
   }
   tst->st_mode = st.st_mode;
   tst->st_size = st.st_size;
   tst->st_uid = st.st_uid;
   tst->st_gid = st.st_gid;
   tst->st_major = 0;
   tst->st_minor = 0;
   if (hostfs_get_meta(path, &meta)) {
      tst->st_mode = meta.mode;
      tst->st_uid = meta.uid;
      tst->st_gid = meta.gid;
      return 0; // Success
   }
   hostfs_set_meta(path, st.st_uid, st.st_gid, st.st_mode);
   return ret;
}

struct tinydirent tinydent;
void* hostfs_readdir(void* sbfs, const char* path, int ndx)
{
   char fullpath[1024];
   char* file = calc_path(fullpath, sbfs, path);
   DIR* dir = opendir(file);
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

bool_t hostfs_can_create(void* sbfs, const char* path, uid_t uid, gid_t gid)
{
   return 1;
}

errno_t  hostfs_mount(device* dev, mountpoint* mount, const char* options)
{
   hostfs_sbfs* sbfs = malloc(sizeof(hostfs_sbfs));
   sbfs->chroot = main_chroot;
   mount->sbfs = sbfs;
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
   mount->mount_can_create = &hostfs_can_create;
   mount->mount_umount = &hostfs_umount;
   return 0;
}

errno_t hostfs_umount(void* sbfs)
{
   if (fmeta) {
      fclose(fmeta);
      fmeta = NULL;
   }
   close_cache();
}
