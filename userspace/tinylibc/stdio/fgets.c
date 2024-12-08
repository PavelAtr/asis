#include <stdio.h>

char *fgets(char* s, int size, FILE* stream)
{
    int i;
    int c;
    for (i = 0; i < size - 1; i++)
    {
		c = getc(stream);
		if (feof(stream))
		{
			fprintf(stdout, "FEOF pos=%d\n", stream->pos);
			return NULL;
		}
		s[i] = c;
		fprintf(stdout, "%c", c);
		if (c == '\n')
		{
			fprintf(stdout, "CR\n");
			break;
		}
    }
    s[i + 1] = '\0';
	fprintf(stdout, "%s", s);
    return s;
}
