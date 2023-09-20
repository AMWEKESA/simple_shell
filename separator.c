#include "shell.h"

/**
 * separate_String - separate the string using a designed separator
 *
 * @val: a pointer to val
 *
 * Return: void
 */

void separate_String(list *val)
{
	char *separator = " \t";
	int x, y, count = 2, len;

	len = str_len(val->input_line);
	if (len)
	{
		if (val->input_line[len - 1] == '\n')
			val->input_line[len - 1] = '\0';
	}

	x = 0;
	while (val->input_line[x])
	{
		y = 0;
		do {
			if (val->input_line[x] == separator[y])
				count++;
			y++;
		} while (separator[y]);
		++x;
	}

	val->tokens = malloc(count * sizeof(char *));
	if (val->tokens == NULL)
	{
		perror(val->process);
		exit(errno);
	}
	x = 0;
	val->tokens[x] = str_dup(str_tok(val->input_line, separator));
	val->cmd = str_dup(val->tokens[0]);
	while (val->tokens[x++])
	{
		val->tokens[x] = str_dup(str_tok(NULL, separator));
	}
}
