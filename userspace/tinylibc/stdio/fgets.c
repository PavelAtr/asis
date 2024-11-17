#include <stdio.h>

char *fgets(char* s, int size, FILE* stream)
{
    int i;
    int c;
    for (i = 0; i < size; i++)
    {
	c = getc(stream);
	if (feof(stream))
	    break;
	if (c == '\n') break;
	s[i] = c;
    }
    s[i] = '\0';
    return s;
}
