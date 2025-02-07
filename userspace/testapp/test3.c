#include <stdio.h>

int main(int argc, char** argv)
{
   namedlist* scope = NULL;
   scope = namedlist_add(scope, "string1", "test1");
   scope = namedlist_add(scope, "string2", "test2");
   scope = namedlist_add(scope, "string3", "test3");
   scope = namedlist_rm(scope, "test3");
   scope = namedlist_rm(scope, "test1");
   scope = namedlist_rm(scope, "test2");
   namedlist* i;
   for (i = scope; i; i = i->next)
       printf("%s\n", i->name);
   printf("name2=%s\n", namedlist_get(scope, "test2"));
   return 0;
}