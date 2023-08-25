#include "s_shell.h"

/**
 * _stok - separates strings and delimiters
 *
 * @line: It´s pointer to line from getline.
 * @delim: delimeter to separate string
 *
 * Return: A pointer to the created token
*/

char *_stok(char *line, char *delim)
{
	int y;
	static char *s;
	char *copys;

	if (line != NULL)
		s = line;

	{
		for (y = 0; delim[y] != '\0'; y++)
		{
			if (*s == delim[y])
			break;
		}
		if (delim[y] == '\0')
		{
			;
		}
	++s;
	}
	copys = s;
	if (*copys == '\0')
		return (NULL);
	while (*s != '\0')
	{
		for (y = 0; delim[y] != '\0'; y++)
		{
			if (*s == delim[y])
			{
				*s = '\0';
				s++;
				return (copys);
			}
		}
	s++;
	}
	return (copys);
}


/**
 * strtoken - separate string
 *
 * @val: pointer to val
 *
 * Return: void
 */

void strtoken(list *val)
{
	char *deli = " \t";
	int x, y, increm = 2, len;

	len = str_len(val->cur);
	if (len)
	{
		if (val->cur[len - 1] == '\n')
			val->cur[len - 1] = '\0';
	}

	x = 0;
	y = 0;
	while (val->cur[x])
	{

		do {
			if (val->cur[x] == deli[y])
				increm++;
			++y;
		} while (deli[y]);
		++x;
	}

	val->tok = malloc(increm * sizeof(char *));
	if (val->tok == NULL)
	{
		perror(val->p_name);
		exit(errno);
	}
	x = 0;
	val->tok[x] = str_dup(strtok(val->cur, deli));
	val->cmd_name = str_dup(val->tok[0]);
	while (val->tok[x++])
	{
		val->tok[x] = str_dup(strtok(NULL, deli));
	}
}
