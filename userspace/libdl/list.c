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
	list* j;
	list* prev = scope;
	for (j = scope; j; j = j->next) {
		if (j->obj == obj)
		{
			prev->next = j->next;
			if (j == scope) {
				scope = j->next;
				free(j);
				break;;
	 	    }
			free(j);
			break;
	    }
	    prev = j;
    }
    return scope;
}
