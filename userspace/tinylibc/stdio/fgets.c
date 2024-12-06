#include <stdio.h>

char *fgets(char* s, int size, FILE* stream)
{
    int i;
    int c;
    for (i = 0; i < size; i++)
    {
	c = getc(stream);
	if (feof(stream))
	    return NULL;
	s[i] = c;
	if (c == '\n') break;
    }
    s[i] = '\0';
    return s;
}
