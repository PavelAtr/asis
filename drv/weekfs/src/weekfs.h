#ifndef _WEEKFS_H
#define _WEEKFS_H

#ifdef __ASYS__
#include "../../../core/include/sys/types.h"
#include "../../../core/include/stdint.h"
#else
#include <types.h>
#endif

#define WEEK_VLARGE

#ifdef WEEK_SMALL
typedef uint16_t bnum_t;
typedef uint16_t bsize_t;
typedef uint32_t len_t;
typedef uint16_t counter_t;
#define WEEK_TYPE "small"
#endif

#ifdef WEEK_LARGE
typedef uint32_t bnum_t;
typedef uint32_t bsize_t;
typedef uint32_t len_t;
typedef uint32_t counter_t;
#define WEEK_TYPE "large"
#endif

#ifdef WEEK_VLARGE
typedef ulong64_t bnum_t;
typedef ulong64_t bsize_t;
typedef ulong64_t len_t;
typedef ulong64_t counter_t;
#define WEEK_TYPE "vlarge"
#endif

struct weekfs_inode {
  unsigned int		i_mode;
  unsigned short		i_opflags;
  uid_t			i_uid;
  gid_t			i_gid;
  unsigned int		i_flags;
};

struct weekfs_dirent {
  bnum_t         d_ino;       /* Inode number */
  len_t 			d_size;		/* Size of file */
  short  d_major;
  short  d_minor;
  char           d_name[256]; /* Null-terminated filename */
};

typedef struct {
  struct weekfs_inode d_inode;
  struct weekfs_dirent d_dirent;
} weekfs_dentry;



typedef int32_t errno_t;
typedef uint8_t bool_t;

typedef void(* seek_func)(void* devparam, len_t offset);
typedef len_t(* read_func)(void* devparam, void* buffer, len_t size);
typedef len_t(* write_func)(void* devparam, const void* buffer, len_t size);

#define DEFAULT_BLOCK_SIZE 4096

extern seek_func cache_seek;
extern read_func cache_read;
extern write_func cache_write;

#define TINY_LABEL_MAX 128

typedef struct {
  char type[16];
  char label[TINY_LABEL_MAX];
  bnum_t bcount;
  bsize_t bsize;
} sbparams;

typedef struct {
  sbparams params;
  void* devparam;
  seek_func cache_seek;
  read_func cache_read;
  write_func cache_write;
  bnum_t alloc_start;
} sblock;

#define WEEK_FREE 0
#define WEEK_DENTRY 1
#define WEEK_DATA 2

#define WEEK_BAD_BNUM (bnum_t)-1

#define WEEK_ROOT_UID 0
#define WEEK_ROOT_GID 0

typedef struct {
  unsigned char type;
  bnum_t parent;
  bnum_t next;
} hblock;

void we_superblock_init(sblock* sb, seek_func _seek,
                        read_func _read, write_func _write);
sblock* we_calc_fs(sblock* sb, len_t sizefs, bsize_t bsize);
void we_format(sblock* sb);
sblock* we_superblock_load(sblock* sb);
void we_superblock_save(sblock* sb);
hblock* we_header_load(sblock* sb, hblock* header, bnum_t ind);
void we_header_save(sblock* sb, hblock* header, bnum_t ind);


len_t we_block_read(sblock* sb, bnum_t bnum, void* data, len_t len, len_t off);
len_t we_block_write(sblock* sb, bnum_t bnum, const void* data, len_t len, len_t off);
bnum_t we_dentry_find(sblock* sb, const char* path, bnum_t* parent);
errno_t we_dentry_create(sblock* sb, const char* path, bnum_t copydata, void* dntry);
len_t we_allocate(sblock* sb, bnum_t ndentry, len_t len);
len_t we_truncate(sblock* sb, bnum_t ndentry, len_t len);
len_t we_calcspace(sblock* sb, bnum_t ndentry);
errno_t we_unlink(sblock* sb, bnum_t ndentry, bool_t keepdata);
len_t we_file_write(sblock* sb, bnum_t ndentry, const void* data, len_t len, len_t off);
len_t we_file_read(sblock* sb, bnum_t ndentry, void* data, len_t len, len_t off);


#endif
