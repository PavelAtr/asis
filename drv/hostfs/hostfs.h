#ifndef _HOSTFS_H
#define _HOSTFS_H
#include "../../core/include/asis.h"
#undef free

typedef struct {
    char* chroot;
} hostfs_sbfs;

errno_t hostfs_mknod(void* sbfs, const char *pathname, uid_t uid, gid_t gid, mode_t mode);
errno_t hostfs_modnod(void* sbfs, const char* pathname, uid_t uid, gid_t gid, mode_t mode);
errno_t hostfs_rmnod(void* sbfs, const char *pathname, uid_t curuid, gid_t curgid);
errno_t hostfs_truncate(void* sb, const char *pathname, len_t len);
errno_t hostfs_link(void* sb, const char* src, const char* dst, bool_t move, uid_t uid, gid_t gid);

errno_t hostfs_stat(void* sbfs, const char* pathname, void* statbuf);
len_t hostfs_fread(void* sbfs, const char* path, void* ptr, len_t size, len_t off);
len_t hostfs_fwrite(void* sbfs, const char* path, const void* ptr, len_t size, len_t off);
void* hostfs_readdir(void* sbfs, const char* path, int ndx);

bool_t hostfs_can_read(void* sbfs, const char* path, uid_t uid, gid_t gid);
bool_t hostfs_can_write(void* sbfs, const char* path, uid_t uid, gid_t gid);
bool_t hostfs_can_execute(void* sbfs, const char* path, uid_t uid, gid_t gid);
bool_t hostfs_can_create(void* sbfs, const char* path, uid_t uid, gid_t gid);
errno_t  hostfs_mount(device* dev, mountpoint* mount, const char* options);
errno_t hostfs_umount(void* sbfs);

#endif
