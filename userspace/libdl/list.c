#include "list.h"

#ifdef __ASIS__
#include <asis.h>
#else
#include <stddef.h>
#include <stdlib.h>
#endif
#include <string.h>

list* list_add(list* scope, aobj obj)
{
	list* new = calloc(1, sizeof(list));
	new->obj = obj;
	if (scope == NULL) {
		return new;
    }
	list* j;
	for (j = scope; j->next; j = j->next);
	j->next = new;
	return scope;
	
}

list* list_rm(list* scope, aobj obj)
{
    if (scope == NULL) {
		return NULL;
    }
    if (scope->obj == obj)
    {
	scope = scope->next;
	free(scope);
    }
    list* prev;
    list* cur;
    list* tofree = NULL;;
    for (prev = scope, cur = scope->next; cur; prev = cur, cur = cur->next)
    {
	if (cur->obj == obj)
	{
	    prev->next = cur->next;
	    tofree = cur;
	}
    }
    if (tofree) free(tofree);
    return scope;
}
