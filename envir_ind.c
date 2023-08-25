#include "s_shell.h"

/**
 * env - shows the environment of shell
 *
 * @val: pointer to val
 *
 * Return: success
 */

int env(list *val)
{
	int x;
	char copyfile[50] = {'\0'};
	char *var_dup = NULL;

	if (val->tok[1] == NULL)
		printenv(val);
	else
	{
		 x = 0;
		while (val->tok[1][x])
		{
			if (val->tok[1][x] == '=')
			{
				var_dup = str_dup(env_key(copyfile, val));
				if (var_dup != NULL)
					key(copyfile, val->tok[1] + x + 1, val);


				 printenv(val);
				if (env_key(copyfile, val) == NULL)
				{
					_print(val->tok[1]);
					_print("\n");
				}
				else
				{
					key(copyfile, var_dup, val);
					free(var_dup);
				}
				return (0);
			}
			copyfile[x] = val->tok[1][x];
			++x;
		}
		errno = 2;
		perror(val->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 *env_set - set environment
 *
 * @val: struct for program val
 *
 * Return: zero on sucess, or other number if declared in the arguments
 */

int env_set(list *val)
{
	if (val->tok[1] == NULL || val->tok[2] == NULL)
		return (0);
	if (val->tok[3] != NULL)
	{
		errno = E2BIG;
		perror(val->cmd_name);
		return (5);
	}

	key(val->tok[1], val->tok[2], val);

	return (0);
}

/**
 * env_unset - unset the environment
 *
 * @val: struct of val
 *
 * Return: succcess
 */

int env_unset(list *val)
{
	if (val->tok[1] == NULL)
		return (0);
	if (val->tok[2] != NULL)
	{
		errno = E2BIG;
		perror(val->cmd_name);
		return (5);
	}
	rm_env(val->tok[1], val);

	return (0);
}
