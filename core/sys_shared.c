#include <asis.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

sharedobj* sharedobjs[MAXSHAREDOBJ];

int_t newshared()
{
    for (int i = 0; i < MAXSHAREDOBJ; i++) {
        if (!sharedobjs[i]) {
            return i;
        }
    }
    return -1; // No available slot
}

int_t findshared(const char* type, const char* path)
{
    for (int i = 0; i < MAXSHAREDOBJ; i++) {
        if (sharedobjs[i] && sharedobjs[i]->type && sharedobjs[i]->path &&
            strcmp(sharedobjs[i]->type, type) == 0 &&
            strcmp(sharedobjs[i]->path, path) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

void* sys_shared(const char* type, const char* path, const char* mode)
{
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
        sharedobjs[index]->type = strdup(type);
        sharedobjs[index]->path = strdup(path);
        if (strcmp(type, "fifo") == 0) {
            sharedobjs[index]->obj = calloc(1, sizeof(pipebuf));
        }
        if (strcmp(type, "sock") == 0) {
            sharedobjs[index]->obj = NULL; /* UNREALIZED */
        }
   }    
   return sharedobjs[index] ? sharedobjs[index]->obj : NULL;
}