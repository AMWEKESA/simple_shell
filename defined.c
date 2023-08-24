#include "s_shell.h"

/**
 * escape - exit program with the status
 *
 * @val: pointer of val
 * Return: always
 */
int escape(list *val)
{
	int x;

	if (val->tok[1] != NULL)
	{
		for (x = 0; val->tok[1][x]; x++)
		{
			if ((val->tok[1][x] < '0' || val->tok[1][x] > '9')
				&& val->tok[1][x] != '+')
			{
				errno = 2;
				return (2);
			}
		}
		errno = _atoi(val->tok[1]);
	}
	free_val(val);
	exit(errno);
}

/**
 * current - change the current directory
 * @val: pointer to val
 * Return: always
 */

int current(list *val)
{
	char *pre = NULL;
	char *c = env_key("HOME", val);
	char prev_dir[128] = {0};
	int err_c = 0;

	if (val->tok[1])
	{
		if (str_cmp(val->tok[1], "-", 0))
		{
			pre = env_key("OLDPWD", val);
			if (pre)
			{
				err_c  = sw_dir(val, pre);
			}
			_print(env_key("PWD", val));
			_print("\n");

			return (err_c);
		}
		else
		{
			return (sw_dir(val, val->tok[1]));
		}
	}
	else
	{
		if (!c)
			c = getcwd(prev_dir, 128);

		return (sw_dir(val, c));
	}
	return (0);
}

/**
 * sw_dir - set the work directory
 *
 * @val: pointer to val
 * @ch: path to be set as work directory
 *
 * Return: always
 */
int sw_dir(list *val, char *ch)
{
	char prev_dir[128] = {0};
	int status = 0;

	getcwd(prev_dir, 128);

	if (!str_cmp(prev_dir, ch, 0))
	{
		status = chdir(ch);
		if (status == -1)
		{
			errno = 2;
			return (3);
		}
		key("PWD", ch, val);
	}
	key("OLDPWD", prev_dir, val);
	return (0);
}

/**
 * for_you - points where shell is running
 *
 * @val: pointer val
 * Return: always
 */

int for_you(list *val)
{
	int i, j = 0;
	char *ch[6] = {NULL};

	ch[0] = HELP1;

	if (val->tok[1] == NULL)
	{
		_print(ch[0] + 6);
		return (1);
	}
	if (val->tok[2] != NULL)
	{
		errno = E2BIG;
		perror(val->cmd_name);
		return (5);
	}
	ch[1] = Q;
	ch[2] = PATH_TEE;
	ch[3] = PATH_ENV;
	ch[4] = UNEN_PATH;
	ch[5] = PATH_CURRENT;

	i = 0;
	for (; ch[i]; i++)
	{
		j = str_len(val->tok[1]);
		if (str_cmp(val->tok[1], ch[i], j))
		{
			_print(ch[i] + j + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(val->cmd_name);
	return (0);
}

/**
 * jina - also
 *
 * @val: pointer to val
 *
 * Return: success
 */

int jina(list *val)
{
	int x = 0;

	if (val->tok[1] == NULL)
		return (print_alias(val, NULL));


	do {
		if (char_count(val->tok[x], "="))
			set_gel(val->tok[x], val);
		else
			    print_alias(val, val->tok[x]);
	} while (val->tok[++x]);
	return (0);
}
