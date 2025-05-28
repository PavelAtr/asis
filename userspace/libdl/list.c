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
	new->next = NULL;
	if (scope == NULL) {
	printf("list added %p\n", new);
		return new;
        }
	list* j;
	for (j = scope; j->next; j = j->next);
	j->next = new;
	printf("list added %p\n", new);
	return scope;
	
}

list* list_rm(list* sc, aobj obj)
{
    list* scope = sc;
    if (scope == NULL) {
		return NULL;
    }
    if (scope->obj == obj)
    {
	scope = scope->next;
	free(sc);
	return scope;
    }
    list* prev = scope;
    list* cur = scope->next;
    while (cur)
    {
	if (cur->obj == obj)
	{
	    prev->next = cur->next;
	    free(cur);
	    break;
	}
	prev = cur;
	cur = cur->next;
    }
    return scope;
}
