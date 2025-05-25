#include "namedlist.h"

#ifdef __ASIS__
#include <asis.h>
#else
#include <stddef.h>
#include <stdlib.h>
#endif
#include <string.h>

namedlist* namedlist_add(namedlist* scope, aobj obj, const char* name)
{
	namedlist* new = calloc(1, sizeof(namedlist));
	new->name = strdup(name);
	new->obj = obj;
	if (scope == NULL) {
		return new;
    }
	namedlist* j;
	for (j = scope; j->next; j = j->next);
	j->next = new;
	return scope;
	
}

namedlist* namedlist_rm(namedlist* scope, const char* name)
{
    if (scope == NULL) {
		return NULL;
    }
	namedlist* j;
	namedlist* prev = scope;
	for (j = scope; j; j = j->next) {
		if (strcmp (j->name, name) == 0)
		{
			prev->next = j->next;
			if (j == scope) {
				scope = j->next;
				free(j->name);
				free(j);
				break;;
	 	    }
			free(j->name);
			free(j);
			break;
	    }
	    prev = j;
    }
    return scope;
}

aobj namedlist_get(namedlist* scope, const char* name)
{
	namedlist* j;
	for (j = scope; j; j = j->next) {
		if (strcmp (j->name, name) == 0) {
			return j->obj;
		}
    }
    return NULL;
}
