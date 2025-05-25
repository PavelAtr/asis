#ifndef _UEFIFS_H
#define _UEFIFS_H
#include "../../core/include/asis.h"

errno_t uefifs_mknod(void* sbfs, const char *pathname, uid_t uid, gid_t gid, mode_t mode);
errno_t uefifs_modnod(void* sbfs, const char* pathname, uid_t uid, gid_t gid, mode_t mode);
errno_t uefifs_rmnod(void* sbfs, const char *pathname, uid_t curuid, gid_t curgid);
errno_t uefifs_truncate(void* sb, const char *pathname, len_t len);
errno_t uefifs_link(void* sb, const char* src, const char* dst, bool_t move, uid_t uid, gid_t gid);

errno_t uefifs_stat(void* sbfs, const char* pathname, void* statbuf);
len_t uefifs_fread(void* sbfs, const char* path, void* ptr, len_t size, len_t off);
len_t uefifs_fwrite(void* sbfs, const char* path, const void* ptr, len_t size, len_t off);
void* uefifs_readdir(void* sbfs, const char* path, int ndx);

bool_t uefifs_can_read(void* sbfs, const char* path, uid_t uid, gid_t gid);
bool_t uefifs_can_write(void* sbfs, const char* path, uid_t uid, gid_t gid);
bool_t uefifs_can_execute(void* sbfs, const char* path, uid_t uid, gid_t gid);
errno_t  uefifs_mount(device* dev, mountpoint* mount, const char* options);

#endif
