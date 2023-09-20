#include "shell.h"

/**
 * add_alias - add aliases
 *
 * @val: pointer to val
 * @alias: name of the alias to be printed
 *
 * Return: sucess
 */

int add_alias(list *val, char *alias)
{
	int x, y, len;
	char buffer[250] = {'\0'};

	if (val->a_list)
	{
		len = str_len(alias);

		x = 0;
		while (val->a_list[x])
		{
			if (!alias || (str_cmp(val->a_list[x], alias, len)
				&&	val->a_list[x][len] == '='))
			{
				for (y = 0; val->a_list[x][y]; ++y)
				{
					buffer[y] = val->a_list[x][y];
					if (val->a_list[x][y] == '=')
						break;
				}
				buffer[y + 1] = '\0';
				append(buffer, "'");
				append(buffer, val->a_list[x] + y + 1);
				append(buffer, "'\n");
				_print(buffer);
			}
			++x;
		}
	}

	return (0);
}

/**
 * show_alias - add, remove or show aliases
 *
 * @val: pointer to val
 * @name: name of the requested alias
 *
 * Return: sucess
 */

char *show_alias(list *val, char *name)
{
	int x, len;

	if (name == NULL || val->a_list == NULL)
	{
		return (NULL);
	}

	len = str_len(name);
	x = 0;

	do {
		if (str_cmp(name, val->a_list[x], len) &&
			val->a_list[x][len] == '=')
		{
			return (val->a_list[x] + len + 1);
		}
		++x;
	} while (val->a_list[x]);

	return (NULL);

}

/**
 * rem_alias - add, or override alias
 *
 * @a_str: alias to be set
 * @val: pointer to val
 *
 * Return: sucess
 */

int rem_alias(char *a_str, list *val)
{
	int x, y;
	char buffer[250] = {'0'}, *temp = NULL;

	if (a_str == NULL ||  val->a_list == NULL)
		return (1);

	x = 0;
	while (a_str[x])
	{
		if (a_str[x] != '=')
			buffer[x] = a_str[x];
		else
		{
			temp = show_alias(val, a_str + x + 1);
			break;
		}
		++x;
	}

	y = 0;
	while (val->a_list[y])
	{
		if (str_cmp(buffer, val->a_list[y], x) &&
			val->a_list[y][x] == '=')
		{
			free(val->a_list[y]);
			break;
		}
		++y;
	}

	if (temp)
	{
		append(buffer, "=");
		append(buffer, temp);
		val->a_list[y] = str_dup(buffer);
	}
	else
		val->a_list[y] = str_dup(a_str);
	return (0);
}
