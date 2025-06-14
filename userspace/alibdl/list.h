#ifndef _NAMED_LIST_H
#define _NAMED_LIST_H


#define NAMED_LIST_ESSENTIAL void* next;

typedef void* aobj;

typedef struct {
   NAMED_LIST_ESSENTIAL
   aobj obj;
} list;

list* list_add(list* scope, aobj obj);

list* list_rm(list* scope, aobj obj);

#define list_geteach_once \
    list* fndlist
#define list_geteach(lst) \
    for (fndlist = (list*)lst; fndlist; fndlist = fndlist->next)

#endif
