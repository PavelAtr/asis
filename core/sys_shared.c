/******************************************************
*  Author: Pavel V Samsonov 2025
*  Author: GitHub Copilot 2025
*******************************************************/

#include <asis.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

sharedobj* sharedobjs[MAXSHAREDOBJ];

int_t newshared()
{
    int i;
    for (i = 0; i < MAXSHAREDOBJ; i++) {
        if (!sharedobjs[i]) {
            return i;
        }
    }
    return -1; // No available slot
}

int_t findshared(const char* type, const char* path)
{
    int i;
    for (i = 0; i < MAXSHAREDOBJ; i++) {
        if (sharedobjs[i] && sharedobjs[i]->type && sharedobjs[i]->path &&
            strcmp(sharedobjs[i]->type, type) == 0 &&
            strcmp(sharedobjs[i]->path, path) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

void* sys_shared(const char* type, const char* path, const char* mode, size_t* out_size)
{
   if ((strcmp(type,"fifo") == 0 ||
       strcmp(type,"sock") == 0) && 
       !(strcmp(mode, "r") == 0 || strcmp(mode, "w") == 0)) {
      current_errno = EPERM;
      return NULL; // Invalid type
   }
   if (mode[0] == '\0') {
    // If mode is empty, we assume no checks are needed
      goto nocheckfs;
   }
   mountpoint* mount = sys_get_mountpoint(path);
   if (!mount) {
      current_errno = ENOENT;
      return 0;
   }
   const char* file = sys_calcpath(mount, path);
   if (strlen(mode) >= 1) {
        if (mode[0] == 'r' && !mount->mount_can_read(mount->sbfs, file,
                             current->uid, current->gid)) {
            current_errno = EPERM;
            return NULL;
        }
    }
   if (strlen(mode) >= 1) {
        if (mode[0] == 'w' && !mount->mount_can_write(mount->sbfs, file,
                            current->uid, current->gid)) {
            current_errno = EPERM;
            return NULL;
        }
    }
nocheckfs:    
   int_t index = findshared(type, path);
   if (index == -1) {
        index = newshared();
        if (index == -1) {
            current_errno = ENOMEM;
            return NULL; // No available slot
        }
        sharedobjs[index] = malloc(sizeof(sharedobj));
        if (!sharedobjs[index]) {
            current_errno = ENOMEM;
            return NULL; // Memory allocation failed
        }
        sharedobjs[index]->refcount = 1;
        sharedobjs[index]->type = strdup(type);
        sharedobjs[index]->path = strdup(path);
        if (strcmp(type, "fifo") == 0) {
            sharedobjs[index]->obj = calloc(1, sizeof(pipebuf));
            sharedobjs[index]->size = sizeof(pipebuf);
            *out_size = sizeof(pipebuf);
        }
        if (strcmp(type, "memfd") == 0) {
            sharedobjs[index]->obj = calloc(1, 1);
            sharedobjs[index]->size = 1;
            *out_size = 1;
        }
   } else {
        if ((strcmp(type, "memfd") == 0)
                && *out_size > sharedobjs[index]->size
                && *out_size != -1) {
            // Resize the memory file if the requested size is larger
            void* new_mem = realloc(sharedobjs[index]->obj, *out_size);
            if (!new_mem) {
                current_errno = ENOMEM;
                return NULL; // Memory allocation failed
            }
            sharedobjs[index]->obj = new_mem;
            sharedobjs[index]->size = *out_size;
        }
        if (*out_size == (size_t)-1) {
            sharedobjs[index]->refcount++;
        }
        *out_size = sharedobjs[index]->size;
    }
 
   return sharedobjs[index] ? sharedobjs[index]->obj : NULL;
}

void sys_delshared(const char* type, const char* path)
{
    int_t index = findshared(type, path);
    if (index == -1) {
        return; // Not found
    }
    sharedobjs[index]->refcount--;
    if (sharedobjs[index]->refcount <= 0) {
        free(sharedobjs[index]->type);
        free(sharedobjs[index]->path);
        free(sharedobjs[index]->obj);
        free(sharedobjs[index]);
        sharedobjs[index] = NULL; // Remove the shared object
    }
}
