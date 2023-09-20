#include "shell.h"

/**
 * current_dir - change current directory
 *
 * @val: pointer to val
 *
 * Return: success
 */

int current_dir(list *val)
{
	int err_code = 0;
	char *home_dir = get_variable("HOME", val), *prev_dir = NULL;
	char old_dir[128] = {0};

	if (val->tokens[1])
	{
		if (str_cmp(val->tokens[1], "-", 0))
		{
			prev_dir = get_variable("OLDPWD", val);
			if (prev_dir)
				err_code = set_working_dir(val, prev_dir);
			_print(get_variable("PWD", val));
			_print("\n");

			return (err_code);
		}
		else
		{
			return (set_working_dir(val, val->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(old_dir, 128);

		return (set_working_dir(val, home_dir));
	}
	return (0);
}
