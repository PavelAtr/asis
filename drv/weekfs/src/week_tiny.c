#include "week_tiny.h"
#include "weekfs.h"
#include <string.h>
#include "../../../core/include/sys/capability.h"

#include <dirent.h>
#include <errno.h>

weekfs_dentry data;
weekfs_dentry data2;
hblock header;

weekfs_dentry* weekfs_getdntry(void* sb, const char* path, weekfs_dentry* buf)
{
   bnum_t parent;
   bnum_t ndentry = we_dentry_find(sb, path, &parent);
   if (ndentry == WEEK_BAD_BNUM) {
      return NULL;
   }
   we_block_read(sb, ndentry, buf, sizeof(weekfs_dentry), 0);
   return buf;
}

bool_t _can_write(uid_t i_uid, gid_t i_gid, mode_t i_mode, uid_t uid, gid_t gid)
{
   if (i_uid == uid && i_mode & S_IWUSR) {
      return 1;
   }
   if (i_gid == gid && i_mode & S_IWGRP) {
      return 1;
   }
   if (i_mode & S_IWOTH) {
      return 1;
   }
   return 0;
}

bool_t _can_read(uid_t i_uid, gid_t i_gid, mode_t i_mode, uid_t uid, gid_t gid)
{
   if (i_uid == uid && i_mode & S_IRUSR) {
      return 1;
   }
   if (i_gid == gid && i_mode & S_IRGRP) {
      return 1;
   }
   if (i_mode & S_IROTH) {
      return 1;
   }
   return 0;
}

bool_t _can_exec(uid_t i_uid, gid_t i_gid, mode_t i_mode, uid_t uid, gid_t gid)
{
   if (i_uid == uid && i_mode & S_IXUSR) {
      return 1;
   }
   if (i_gid == gid && i_mode & S_IXGRP) {
      return 1;
   }
   if (i_mode & S_IXOTH) {
      return 1;
   }
   return 0;
}

errno_t weekfs_mknod(void* sb, const char *pathname, uid_t uid, gid_t gid, mode_t mode)
{
   bnum_t parent;
   we_dentry_find(sb, pathname, &parent);
   if (parent == WEEK_BAD_BNUM) {
      return ENOENT;
   }
   we_block_read(sb, parent, &data, sizeof(weekfs_dentry), 0);
   if (!(data.d_inode.i_mode & S_IFDIR)) {
      return ENOTDIR;
   }
   if (!(_can_write(data.d_inode.i_uid, data.d_inode.i_gid, data.d_inode.i_mode, uid, gid)
         || security->capable(CAP_DAC_OVERRIDE))) {
      return EPERM;
   }
   memset(&data, 0x0, sizeof(weekfs_dentry));
   data.d_inode.i_mode = mode;
   data.d_inode.i_uid = uid;
   data.d_inode.i_gid = gid;
   return we_dentry_create(sb, pathname, 0, &data);
}

errno_t weekfs_modnod(void* sb, const char* pathname, uid_t uid, gid_t gid, mode_t mode)
{
   bnum_t parent;
   bnum_t curdntr = we_dentry_find(sb, pathname, &parent);
   if (curdntr == WEEK_BAD_BNUM) {
      return ENOENT;
   }
   we_block_read(sb, curdntr, &data, sizeof(weekfs_dentry), 0);
   data.d_inode.i_mode = mode;
   data.d_inode.i_uid = uid;
   data.d_inode.i_gid = gid;
   we_block_write(sb, curdntr, &data, sizeof(weekfs_dentry), 0);
   return 0;
}

errno_t weekfs_link(void* sb, const char* src, const char* dst, bool_t move, uid_t uid, gid_t gid)
{
   bnum_t parent;
   bnum_t curdntr = we_dentry_find(sb, src, &parent);
   if (curdntr == WEEK_BAD_BNUM) {
      return ENOENT;
   }
   we_block_read(sb, curdntr, &data, sizeof(weekfs_dentry), 0);
   bnum_t newparent;
   bnum_t newdntr = we_dentry_find(sb, dst, &newparent);
   if (newparent == WEEK_BAD_BNUM) {
      return ENOENT;
   }
   we_block_read(sb, parent, &data2, sizeof(weekfs_dentry), 0);
   if (!(data2.d_inode.i_mode & S_IFDIR)) {
      return ENOTDIR;
   }
   if (!(_can_write(data2.d_inode.i_uid, data2.d_inode.i_gid, data2.d_inode.i_mode, uid, gid)
         || security->capable(CAP_DAC_OVERRIDE))) {
      return EPERM;
   }
   if (data.d_inode.i_mode & S_IFDIR) {
      if (!(_can_write(data.d_inode.i_uid, data.d_inode.i_gid, data.d_inode.i_mode, uid, gid)
            || security->capable(CAP_DAC_OVERRIDE))) {
         return EPERM;
      }
      char* name = strrchr(dst, '/');
      name = (name[0] == '/') ? name + 1 : name;
      strcpy(data.d_dirent.d_name, name);
      we_header_load(sb, &header, curdntr);
      header.parent = newparent;
      we_header_save(sb, &header, curdntr);
      we_block_write(sb, curdntr, &data, sizeof(weekfs_dentry), 0);
      return 0;
   }
   errno_t ret = we_dentry_create(sb, dst, curdntr, &data);
   if (ret) {
      return ret;
   }
   if (move) {
      we_unlink(sb, curdntr, 1);
   }
   return 0;
}


errno_t weekfs_rmnod(void* sb, const char *pathname, uid_t uid, gid_t gid)
{
   bnum_t parent;
   bnum_t ndntr = we_dentry_find(sb, pathname, &parent);
   if (ndntr == WEEK_BAD_BNUM) {
      return ENOENT;
   }
   we_block_read(sb, parent, &data, sizeof(weekfs_dentry), 0);
   if (!(data.d_inode.i_mode & S_IFDIR)) {
      return ENOTDIR;
   }
   if (!(_can_write(data.d_inode.i_uid, data.d_inode.i_gid, data.d_inode.i_mode, uid, gid)
         || security->capable(CAP_DAC_OVERRIDE))) {
      return EPERM;
   }
   return we_unlink(sb, ndntr, 0);
}

errno_t weekfs_truncate(void* sb, const char *pathname, len_t len)
{
   bnum_t parent;
   bnum_t ndntr = we_dentry_find(sb, pathname, &parent);
   if (ndntr == WEEK_BAD_BNUM) {
      return ENOENT;
   }
   we_truncate(sb, ndntr, len);
   return 0;
}

len_t weekfs_read(void* sb, const char* path, void* buf, len_t size, len_t offset)
{
   bnum_t parent;
   bnum_t ndentry = we_dentry_find(sb, path, &parent);
   if (ndentry == WEEK_BAD_BNUM) {
      return 0;
   }
   return we_file_read(sb, ndentry, buf, size, offset);
}

len_t weekfs_write(void* sb, const char* path,const void* buf, len_t size, len_t offset)
{
   bnum_t parent;
   bnum_t ndentry = we_dentry_find(sb, path, &parent);
   if (ndentry == WEEK_BAD_BNUM) {
      return 0;
   }
   return we_file_write(sb, ndentry, buf, size, offset);
}

bool_t weekfs_can_read(void* sb, const char* path, uid_t uid, gid_t gid)
{
   weekfs_getdntry(sb, path, &data);
   return _can_read(data.d_inode.i_uid, data.d_inode.i_gid, data.d_inode.i_mode, uid, gid);
}

bool_t weekfs_can_write(void* sb, const char* path, uid_t uid, gid_t gid)
{
   weekfs_getdntry(sb, path, &data);
   return _can_write(data.d_inode.i_uid, data.d_inode.i_gid, data.d_inode.i_mode, uid, gid);
}

bool_t weekfs_can_execute(void* sb, const char* path, uid_t uid, gid_t gid)
{
   weekfs_getdntry(sb, path, &data);
   return _can_exec(data.d_inode.i_uid, data.d_inode.i_gid, data.d_inode.i_mode, uid, gid);
}

errno_t weekfs_stat(void* sb, const char* pathname, void* buf)
{
   struct tinystat* statbuf = buf;
   weekfs_dentry data;
   bnum_t parent;
   bnum_t ndentry = we_dentry_find(sb, pathname, &parent);
   if (ndentry == WEEK_BAD_BNUM) {
      return -1;
   }
   we_block_read(sb, ndentry, &data, sizeof(weekfs_dentry), 0);
   statbuf->st_mode = data.d_inode.i_mode;
   statbuf->st_uid = data.d_inode.i_uid;
   statbuf->st_gid = data.d_inode.i_gid;
   statbuf->st_size = data.d_dirent.d_size;
   return 0;
}

struct tinydirent tinydnt;
void* weekfs_readdir(void* sbfs, const char* path, int ndx)
{
   sblock* sb = sbfs;
   bnum_t parent;
   bnum_t i = 0;
   bnum_t bnum;
   weekfs_dentry dent;
   bool_t found = 0;
   hblock header;
   bnum_t ndentry = we_dentry_find(sb, path, &parent);
   if (ndentry == WEEK_BAD_BNUM) {
      return NULL;
   }
   for (bnum = 0; bnum < sb->params.bcount; bnum++) {
      we_header_load(sb, &header, bnum);
      if (header.type == WEEK_DENTRY && header.parent == ndentry && bnum != ndentry) {
         we_block_read(sb, bnum, &dent, sizeof(weekfs_dentry), 0);
         if (i == (bnum_t)ndx) {
            found = 1;
            strcpy(tinydnt.d_name, dent.d_dirent.d_name);
            break;
         }
         i++;
      }
   }
   if (found) {
      return &tinydnt;
   } else {
      return NULL;
   }
}


errno_t  weekfs_mount(device* dev, mountpoint* mount, const char* options)
{
   sblock* sb = sys_malloc(sizeof(sblock));
   we_superblock_init(sb, dev->dev_seek, dev->dev_read, dev->dev_write);
   sb->devparam = dev->devparams;
   we_superblock_load(sb);
   sb->alloc_start = 0;
   if (strcmp(sb->params.type, WEEK_TYPE) != 0) {
      sys_printf("ERROR! fstype=%s != compile=%s\n", sb->params.type, WEEK_TYPE);
   } else {
      sys_printf("weekfs: bs=%d, bcount=%d type=%s\n", sb->params.bsize, sb->params.bcount, sb->params.type);
   }
   mount->sbfs = sb;
   mount->mount_mknod = &weekfs_mknod;
   mount->mount_modnod = &weekfs_modnod;
   mount->mount_rmnod = &weekfs_rmnod;
   mount->mount_link = &weekfs_link;
   mount->mount_truncate = &weekfs_truncate;
   mount->mount_stat =  &weekfs_stat;
   mount->mount_fread = &weekfs_read;
   mount->mount_fwrite = &weekfs_write;
   mount->mount_readdir = &weekfs_readdir;
   mount->mount_can_read = &weekfs_can_read;
   mount->mount_can_write = &weekfs_can_write;
   mount->mount_can_execute = &weekfs_can_execute;
   return 0;
}
