#include "shell.h"

/**
 * alias_toolkit - add, remove or show aliases
 *
 * @val: pointer to val
 *
 * Return: success
 */

int alias_toolkit(list *val)
{
	int x = 0;

	if (val->tokens[1] == NULL)
		return (add_alias(val, NULL));

	while (val->tokens[++x])
	{
		if (char_count(val->tokens[x], "="))
			rem_alias(val->tokens[x], val);
		else
			add_alias(val, val->tokens[x]);
	}

	return (0);
}
