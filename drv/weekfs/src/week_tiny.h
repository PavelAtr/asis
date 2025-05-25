#ifndef _WEEK_TINY_H
#define _WEEK_TINY_H
#include "../../../core/include/asis.h"
#include "weekfs.h"
#include <sys/stat.h>
#include <sys/types.h>

weekfs_dentry* weekfs_getdntry(void* sb, const char* path, weekfs_dentry* buf);
errno_t weekfs_mknod(void* sb, const char *pathname, uid_t uid, gid_t gid, mode_t mode);
errno_t weekfs_modnod(void* sb, const char* pathname, uid_t uid, gid_t gid, mode_t mode);
errno_t weekfs_link(void* sb, const char* src, const char* dst, bool_t move, uid_t uid, gid_t gid);
errno_t weekfs_rmnod(void* sb, const char *pathname, uid_t curuid, gid_t curgid);
errno_t weekfs_truncate(void* sb, const char *pathname, len_t len);
errno_t weekfs_stat(void* sb, const char* pathname, void* statbuf);
void* weekfs_readdir(void* sbfs, const char* path, int ndx);
len_t weekfs_read(void* sb, const char* path, void* buf, len_t size, len_t offset);
len_t weekfs_write(void* sb, const char* path, const void* buf, len_t size, len_t offset);
bool_t weekfs_can_read(void* sb, const char* path, uid_t uid, gid_t gid);
bool_t weekfs_can_write(void* sb, const char* path, uid_t uid, gid_t gid);
bool_t weekfs_can_execute(void* sb, const char* path, uid_t uid, gid_t gid);
errno_t  weekfs_mount(device* dev, mountpoint* mount, const char* options);

#endif
