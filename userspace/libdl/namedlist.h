#ifndef _NAMED_LIST_H
#define _NAMED_LIST_H


#define NAMED_LIST_ESSENTIAL \
   char* name; \
   void* next;

typedef void* aobj;

typedef struct {
   NAMED_LIST_ESSENTIAL
   aobj obj;
} namedlist;

namedlist* namedlist_add(namedlist* scope, aobj obj, const char* name);
namedlist* namedlist_rm(namedlist* scope, const char* name);
aobj namedlist_get(namedlist* scope, const char* name);

#endif
