#include "shell.h"

/**
 * str_tok - separates strings with sepiters
 *
 * @line: pointer getline
 * @sep: pointer to separators
 *
 * Return: A pointer to the created token
*/

char *str_tok(char *line, char *sep)
{
	int x;
	static char *ch;
	char *s;

	if (line != NULL)
	{
		ch = line;
	}

	do {
		for (x = 0; sep[x] != '\0'; x++)
		{
			if (*ch == sep[x])
			break;
		}
		if (sep[x] == '\0')
			break;
	} while (*ch != '\0');

	s = ch;
	if (*s == '\0')
		return (NULL);

	do {
		for (x = 0; sep[x] != '\0'; x++)
		{
			if (*ch == sep[x])
			{
				*ch = '\0';
				ch++;
				return (s);
			}
		}
		ch++;
	} while (*ch != '\0');

	return (s);
}
