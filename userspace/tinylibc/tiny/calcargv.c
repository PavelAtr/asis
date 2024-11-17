#include <string.h>

int calcargv(char* cmdline, char** out)
{
	int argc = 0; 
	char quote = 0;
	if (out) out[argc] = &cmdline[0];
	for (short i = 0; cmdline[i] != '\0'; i++)
	{
		if (cmdline[i] == '"')
		{
		    if (quote)
		    {
			quote = 0;
			continue;
		    }
		    quote = 1;
		}
		if (cmdline[i] == ' ' && !quote)
		{
			cmdline[i] = '\0';
			argc++;
			if (out)
				out[argc] = &cmdline[i + 1];
		}
	}
	argc++;
	if (out)
	    out[argc] = NULL;
	argc++;
	return argc;
}

char* unquote(char* str)
{
    if (str[strlen(str) - 1] == '"') str[strlen(str) - 1] = '\0';
    if (str[0] == '"') return &str[1];
	else return str;
}
