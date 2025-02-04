#ifndef _NAMED_LIST_H
#define _NAMED_LIST_H


#define NAMED_LIST_ESSENTIAL \
   const char* name; \
   void* next;

typedef void* aobj;

typedef struct {
   NAMED_LIST_ESSENTIAL
   aobj obj;
} namedlist;

void namedlist_add(namedlist* scope, namedlist* list);
void namedlist_rm(namedlist* scope, const char* name);
aobj namedlist_get(namedlist* scope, const char* name);

#endif
