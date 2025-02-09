#include "hostfs.h"

#ifndef UEFI
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#endif

errno_t hostfs_mknod(void* sbfs, const char *pathname, uid_t uid, gid_t gid,
   mode_t mode)
{
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
   return 0;
}

errno_t hostfs_truncate(void* sb, const char *pathname, len_t len)
{
   return 0;
}

errno_t hostfs_link(void* sb, const char* src, const char* dst, bool_t move,
   uid_t uid, gid_t gid)
{
   return 0;
}

len_t hostfs_fread(void* sbfs, const char* path, void* ptr, len_t size,
   len_t off)
{
   FILE* f;
   len_t ret = 0;
      f = fopen(path, "r");
      if (!f) {
         return 0;
      }
   fseek(f, off, SEEK_SET);
   ret = fread(ptr, 1, size, f);
   fclose(f);
   return ret;
}

len_t hostfs_fwrite(void* sbfs, const char* path, const void* ptr, len_t size,
   len_t off)
{
   FILE* f;
   len_t ret = 0;
      f = fopen(path, "r+");
      if (!f) {
         return 0;
      }
   fseek(f, off, SEEK_SET);
   ret = fwrite(ptr, 1, size, f);
   fclose(f);
   return ret;
}

errno_t hostfs_stat(void* sbfs, const char* pathname, void* statbuf)
{
   struct stat st;
   struct tinystat* tst = statbuf;
   errno_t ret = stat(pathname, &st);
   tst->st_mode = st.st_mode;
   tst->st_size = st.st_size;
#ifdef UEFI
   tst->st_uid = 0;
   tst->st_gid = 0;
   tst->st_major = 0;
   tst->st_minor = 0;
#else
   tst->st_uid = st.st_uid;
   tst->st_gid = st.st_gid;
   tst->st_major = 0;
   tst->st_minor = 0;
#endif
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
