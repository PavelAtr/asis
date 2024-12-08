#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include "weekfs.h"
#include <string.h>




#ifdef WEEK_SMALLMEMORY
hblock temp_header;
weekfs_dentry temp_dentry;
#endif

sblock* we_calc_fs(sblock* sb, len_t sizefs, bsize_t bsize)
{
  sb->params.bsize = bsize;
  sb->params.bcount = (sizefs - sizeof(sblock)) / (bsize + sizeof(hblock));
  if (sizeof(weekfs_dentry) > bsize)
    printf("WARNING! Dentry size=%ld less than bsize=%d!\n", sizeof(weekfs_dentry), bsize);
  return sb;
}

void we_format(sblock* sb)
{
  weekfs_dentry root;
  memset(&root, 0x0, sizeof(weekfs_dentry));
  hblock header;
  memset(&header, 0x0, sizeof(header));
  strcpy(sb->params.type, WEEK_TYPE);
  we_superblock_save(sb);
  bnum_t i;
  for (i = 0; i < sb->params.bcount; i++) {
    if (i == 0) {
      header.type = WEEK_DENTRY;
      header.parent = 0;
      header.next = 0;
    } else {
      header.type = WEEK_FREE;
    }
    we_header_save(sb, &header, i);
  }
  strcpy(root.d_dirent.d_name, "");
  root.d_inode.i_mode = S_IFDIR | 0755;
  root.d_inode.i_uid = WEEK_ROOT_UID;
  root.d_inode.i_gid = WEEK_ROOT_GID;
  we_block_write(sb, 0, &root, sizeof(weekfs_dentry), 0);
}

len_t we_block_read(sblock* sb, bnum_t bnum, void* data, len_t len, len_t off)
{
  len_t size = (len <= sb->params.bsize - off)? len : sb->params.bsize - off;
  sb->cache_seek(sb->devparam, sizeof(sblock) + sizeof(hblock) * sb->params.bcount + sb->params.bsize *  bnum + off);
  len_t readed = sb->cache_read(sb->devparam, data, size);
  return readed;
}

len_t we_block_write(sblock* sb, bnum_t bnum, const void* data, len_t len, len_t off)
{
  len_t size = (len <= sb->params.bsize - off)? len : sb->params.bsize - off;
  sb->cache_seek(sb->devparam, sizeof(sblock) + sizeof(hblock) * sb->params.bcount + sb->params.bsize *  bnum + off);
  len_t writed = sb->cache_write(sb->devparam, data, size);
  return writed;
}

void we_superblock_init(sblock* sb, seek_func _seek, read_func _read, write_func _write)
{
  sb->cache_seek = _seek;
  sb->cache_read = _read;
  sb->cache_write =_write;
}

sblock* we_superblock_load(sblock* sb)
{
  sb->cache_seek(sb->devparam, 0);
  sb->cache_read(sb->devparam, &sb->params, sizeof(sbparams));
  return sb;
}

void we_superblock_save(sblock* sb)
{
  sb->cache_seek(sb->devparam, 0);
  sb->cache_write(sb->devparam, &sb->params, sizeof(sbparams));
}

hblock* we_header_load(sblock* sb, hblock* header, bnum_t ind)
{
  sb->cache_seek(sb->devparam, sizeof(sblock) + sizeof(hblock) * ind);
  sb->cache_read(sb->devparam, header, sizeof(hblock));
  return header;
}

void we_header_save(sblock* sb, hblock* header, bnum_t ind)
{
  sb->cache_seek(sb->devparam, sizeof(sblock) + sizeof(hblock) * ind);
  sb->cache_write(sb->devparam, header, sizeof(hblock));
}

bnum_t we_block_new(sblock* sb)
{
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
#endif
  bnum_t i;
  for (i = sb->alloc_start; i < sb->params.bcount; i++) {
    hblock* header = &temp_header;
    we_header_load(sb, header, i);
    if (header->type == WEEK_FREE) return i;
  }
  return WEEK_BAD_BNUM;
}

counter_t path_total_parts(const char* path)
{
  counter_t ind = 0;
  counter_t count = 0;
  while (path[ind] != '\0') {
    if (path[ind] == '/') count++;
    ind++;
  }
  return count;
}

bool_t path_cmp(const char* path, const char* part, counter_t startpart)
{
  counter_t pathind = 0;
  counter_t partind = 0;
  counter_t partnum = 0;
  const char* tmp = path;;
  bool_t equal = 1;
  while (partnum < startpart) {
    tmp = strchr(tmp, '/') + 1;
    partnum++;
  }
  while (part[partind] != '\0') {
    if (tmp[pathind++] != part[partind++])
      equal = 0;
  }
  if (!(tmp[pathind] == '\0' || tmp[pathind] == '/'))
    equal = 0;
  return equal;
}

bnum_t we_dentry_find(sblock* sb, const char* path, bnum_t* parent)
{
  bnum_t partfound = 0;
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
  weekfs_dentry temp_dentry;
#endif
  weekfs_dentry* dent = &temp_dentry;
  counter_t partcount = path_total_parts(path);
  counter_t partind;
  bnum_t bnum;
  for (partind = 0; partind <= partcount; partind++) {
    *parent = partfound;
    partfound = WEEK_BAD_BNUM;
    for (bnum = 0; bnum < sb->params.bcount; bnum++) {
      hblock* header = &temp_header;
      we_header_load(sb, header, bnum);
      if (header->type == WEEK_DENTRY && header->parent == *parent) {
        we_block_read(sb, bnum, dent, sizeof(weekfs_dentry), 0);
        if (path_cmp(path, dent->d_dirent.d_name, partind)) {
          partfound = bnum;
          break;
        }
      }
    }
    if (partfound == WEEK_BAD_BNUM) {
      if (partind != partcount)
        *parent = WEEK_BAD_BNUM;
      return WEEK_BAD_BNUM;
    }
  }
  return bnum;
}

errno_t we_dentry_create(sblock* sb, const char* path, bnum_t copydata, void* dntry)
{
  bnum_t parent;
  bnum_t self = we_dentry_find(sb, path, &parent);
  weekfs_dentry* data = (weekfs_dentry*) dntry;
  if (parent == WEEK_BAD_BNUM)
    return ENOENT;
  if (self != WEEK_BAD_BNUM)
    return EEXIST;
  bnum_t i = we_block_new(sb);
  if (i == WEEK_BAD_BNUM)
    return ENOMEM;
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
#endif
  hblock* header = &temp_header;
  bnum_t file = 0;
  if (copydata != 0) {
    we_header_load(sb, header, copydata);
    file = header->next;
  }
  we_header_load(sb, header, i);
  header->type = WEEK_DENTRY;
  header->parent = parent;
  header->next = file;
  we_header_save(sb, header, i);
  char* name = strrchr(path, '/');
  name = (name[0] == '/') ? name + 1 : name;
  strcpy(data->d_dirent.d_name, name);
  data->d_dirent.d_ino = i;
  data->d_dirent.d_size = 0;
  we_block_write(sb, i, data, sizeof(weekfs_dentry), 0);
  return 0;
}

len_t we_allocate(sblock* sb, bnum_t ndentry, len_t len)
{
  len_t allocated = 0;
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
#endif
  hblock* header = &temp_header;
  bnum_t prev = ndentry;
  while(allocated < len) {
    bnum_t next;
    we_header_load(sb, header, prev);
    if ((next = header->next) == 0) {
      next = we_block_new(sb);
      if (next == WEEK_BAD_BNUM)
        break;
      header->next = next;
      we_header_save(sb, header, prev);
    }
    we_header_load(sb, header, next);
    if (header->type == WEEK_FREE) {
      header->type = WEEK_DATA;
      header->parent = WEEK_BAD_BNUM;
      header->next = 0;
      we_header_save(sb, header, next);
    }
    allocated += sb->params.bsize;
    prev = next;
  }
  return allocated;
}

len_t we_truncate(sblock* sb, bnum_t ndentry, len_t len)
{
  len_t allocated = 0;
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
  weekfs_dentry temp_dentry;
#endif
  hblock* header = &temp_header;
  we_header_load(sb, header, ndentry);
  bnum_t next = header->next;
  bnum_t cur;
  while (next != 0) {
    cur = next;
    we_header_load(sb, header, next);
    next = header->next;
    allocated += sb->params.bsize;
    if (allocated >= len + sb->params.bsize) {
      allocated -= sb->params.bsize;
      header->type = WEEK_FREE;
      header->next = 0;
      we_header_save(sb, header, cur);
    }
  }
  allocated = (allocated < len)? allocated : len;
  we_block_read(sb, ndentry, &temp_dentry, sizeof(weekfs_dentry), 0);
  temp_dentry.d_dirent.d_size = allocated;
  we_block_write(sb, ndentry, &temp_dentry, sizeof(weekfs_dentry), 0);
  return allocated;
}

len_t we_calcspace(sblock* sb, bnum_t ndentry)
{
  len_t space = 0;
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
#endif
  hblock* header = &temp_header;
  we_header_load(sb, header, ndentry);
  bnum_t next;
  while ((next = header->next) != 0) {
    space += sb->params.bsize;
    we_header_load(sb, header, next);
  }
  return space;
}

errno_t we_unlink(sblock* sb, bnum_t ndentry, bool_t keepdata)
{
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
#endif
  hblock* header = &temp_header;
  we_header_load(sb, header, ndentry);
  bnum_t cur = ndentry;
  while (1) {
    header->type = WEEK_FREE;
    we_header_save(sb, header, cur);
    if (keepdata) break;
    if ((cur = header->next) == 0) break;
    we_header_load(sb, header, cur);
  }
  return 0;
}

len_t we_file_write(sblock* sb, bnum_t ndentry, const void* data, len_t len, len_t off)
{
  we_allocate(sb, ndentry, len + off);
  len_t writed = 0;
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
  weekfs_dentry temp_dentry;
#endif
  hblock* header = &temp_header;
  we_header_load(sb, header, ndentry);
  bnum_t cur;
  len_t size = 0;
  while ((cur = header->next) != 0) {
    we_header_load(sb, header, cur);
    if (header->type != WEEK_DATA) break;
    size += sb->params.bsize;
    len_t block_off = off + writed - (size - sb->params.bsize);
    len_t block_len = (len + off > size)? size - (off + writed) : sb->params.bsize -(size - (len + off));
    if (block_off >= 0 && block_off <= sb->params.bsize)
      writed += we_block_write(sb, cur, data + writed, block_len, block_off);
    if (writed >= len) break;
  }
  we_block_read(sb, ndentry, &temp_dentry, sizeof(weekfs_dentry), 0);
  if (temp_dentry.d_dirent.d_size < off + writed) {
    temp_dentry.d_dirent.d_size = off + writed;
    we_block_write(sb, ndentry, &temp_dentry, sizeof(weekfs_dentry), 0);
  }
  return writed;
}

len_t we_file_read(sblock* sb, bnum_t ndentry, void* data, len_t len, len_t off)
{
  len_t readed = 0;
#ifndef WEEK_SMALLMEMORY
  hblock temp_header;
  weekfs_dentry temp_dentry;
#endif
  hblock* header = &temp_header;
  we_header_load(sb, header, ndentry);
  bnum_t cur;
  len_t size = 0;
  we_block_read(sb, ndentry, &temp_dentry, sizeof(weekfs_dentry), 0);
  len_t newlen = (temp_dentry.d_dirent.d_size - off < len) ?
                 temp_dentry.d_dirent.d_size - off : len;
  while ((cur = header->next) != 0) {
    we_header_load(sb, header, cur);
    if (header->type != WEEK_DATA) break;
    size += sb->params.bsize;
    len_t block_off = off + readed - (size - sb->params.bsize);
    len_t block_len = (newlen + off > size)? size - (off + readed) : sb->params.bsize - (size - (newlen + off));
    if (block_off >= 0 && block_off <= sb->params.bsize)
      readed += we_block_read(sb, cur, data + readed, block_len, block_off);
    if (readed >= newlen) break;
  }
  return readed;
}


