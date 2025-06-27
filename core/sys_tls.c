#include "../config.h"
#include <asis.h>
#include "../userspace/alibdl/libdl.h"

#include <stddef.h>
#include <string.h>



int init_tls(proc* task) {
    dlhandle* hndl = (dlhandle*)task->dlhndl;
    unsigned int max_module_id = 0;
    dlhandle* j;
    for (j = hndl; j; j = j->next) {
        dl* s = j->obj;
        if (!s) {
            continue;
        }
        if (s->module_id > max_module_id) {
            max_module_id = s->module_id; // Find the highest module ID
        }
    }
    task->dtv = sys_calloc(max_module_id + 1, sizeof(char*));
    for (j = hndl; j; j = j->next) {
        dl* s = j->obj;
        if (!s) {
            continue;
        }
        if (s->tls_size == 0) {
            continue; // No TLS for this module
        }
        task->dtv[s->module_id] = sys_malloc(s->tls_size);
        if (!task->dtv[s->module_id]) {
            return -1; // Memory allocation failed
        }
        tls_init(s, task->dtv[s->module_id], s->tls_size);
        printf("TLSINIT: module %d, size %ld address %p\n", s->module_id, s->tls_size, task->dtv[s->module_id]);
    }
    return 0;
}

int deinit_tls(proc* task) {
    if (!task || !task->dtv){
        return -1; // Invalid task or DTV
    }
    dlhandle* hndl = (dlhandle*)task->dlhndl;
    if (!hndl || !hndl->obj) {
        return -1; // Invalid handle or object
    }   
    dlhandle* j;
    for (j = hndl; j; j = j->next) {
        dl* s = j->obj;
        if (!s) {
            continue;
        }
        if (s->tls_size == 0) {
            continue; // No TLS for this module
        }
        if (task->dtv[s->module_id]) {
            printf("FREE_TLS: module %d, address %p\n", s->module_id, task->dtv[s->module_id]);
            sys_free(task->dtv[s->module_id]);
            task->dtv[s->module_id] = NULL;
        }
    }
   sys_free(task->dtv);
    task->dtv = NULL;
    return 0;
}

void* sys_tls_get_addr (unsigned long ti_module, unsigned long ti_offset)
{
   void* ret = current->dtv[ti_module] + ti_offset;
   return ret;
}
