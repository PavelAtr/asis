#include "../config.h"
#include <asis.h>
#include "../userspace/libdl/libdl.h"

#include <stddef.h>



int init_tls(proc* task) {
    dlhandle* hndl = (dlhandle*)task->dlhndl;   
    task->dtv = sys_calloc(max_module_count, sizeof(char*));
    dlhandle* j;
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
        printf("TLSINIT: module %d, size %zu, address %p\n", s->module_id, s->tls_size, task->dtv[s->module_id]);
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
            printf("DEINIT_TLS: module %d, address %p\n", s->module_id, task->dtv[s->module_id]);
            sys_free(task->dtv[s->module_id]);
            task->dtv[s->module_id] = NULL;
        }
    }
   sys_free(task->dtv);
    task->dtv = NULL;
    return 0;
}

void tls_switch(proc* task) {
    if (!task || !task->dtv) {
        return; // Invalid task or DTV
    }
    void (*__tls_init)(char** dtv_ptr) = sys_dlsym(task->dlhndl, "__tls_init");
    if (__tls_init) {
        __tls_init(task->dtv);
    }
}   
