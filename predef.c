#include "s_shell.h"

/**
 * predef - predefines some environment funcs
 *
 * @val: struct for the program's val
 * Return: Success always
 */

int predef(list *val)
{
	int x;
	typedef struct
	{
		char *pick;
		int (*function)(list *);
	} pick_function;

	pick_function choices[] = {
		{"exit", escape},
		{"help", for_you},
		{"cd", current},
		{"alias", jina},
		{"env", env},
		{"setenv", env_set},
		{"unsetenv", env_unset},
		{NULL, NULL}
	};

	for (x = 0; choices[x].pick != NULL; x++)
	{
		if (str_cmp(choices[x].pick, val->cmd_name, 0))
		{
			return (choices[x].function(val));
		}
	}
	return (-1);
}
