#include "shell.h"

/**
 * check_predefined - search for match and execute the associate builtin
 * 
 * @val: pointer to val
 * 
 * Return: function executed, else -1
 */

int check_predefined(list *val)
{
	int n;
	builtins check_list[] = {
		{"exit", terminate},
		{"cd", current_dir},
		{"alias", alias_toolkit},
		{"setting", show_setting},
		{"getsetting", get_setting},
		{"remsetting", rem_setting},
		{NULL, NULL}
	};

	for (n = 0; check_list[n].builtin != NULL; n++)
	{
		if (str_cmp(check_list[n].builtin, val->cmd, 0))
		{
			return (check_list[n].function(val));
		}
	}
	return (-1);
}
