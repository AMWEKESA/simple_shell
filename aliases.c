#include "s_shell.h"

/**
 * gel - handle alliases
 *
 * @val: pointer to val
 * @jina: requested alias
 *
 * Return: success
 */

char *gel(list *val, char *jina)
{
	int x, len;

	if (jina == NULL || val->tee == NULL)
		return (NULL);

	len = str_len(jina);

	do {
		if (str_cmp(jina, val->tee[x], len) &&
			val->tee[x][len] == '=')
		{
			return (val->tee[x] + len + 1);
		}
		++x;
	} while (val->tee[x]);

	return (NULL);

}


/**
 * set_gel - add, or override jina
 *
 * @c: pointer to character
 * @val: pointer to val
 * Return: success
 */

int set_gel(char *c, list *val)
{
	int x = 0, y;
	char buf[250] = {'0'}, *temp = NULL;

	if (c == NULL ||  val->tee == NULL)
		return (1);

	for (; c[x]; ++x)
	{
		if (c[x] != '=')
			buf[x] = c[x];
		else
		{
			temp = gel(val, c + x + 1);
			break;
		}
	}
	y = 0;
	while (val->tee[y])
	{
		if (str_cmp(buf, val->tee[y], x) &&
			val->tee[y][x] == '=')
		{
			free(val->tee[y]);
			break;
		}
		++y;
	}

	if (temp)
	{
		buf_ext(buf, "=");
		buf_ext(buf, temp);
		val->tee[y] = str_dup(buf);
	}
	else
	{
		val->tee[y] = str_dup(c);
	}
	return (0);
}


/**
 * print_alias - handle aliases
 *
 * @val: pointer to val
 * @jina: printer to alias
 *
 * Return: sucess
 */

int print_alias(list *val, char *jina)
{
	int x, y, len;
	char buf[250] = {'\0'};

	if (val->tee)
	{
		len = str_len(jina);
		x = 0;
		do {
			if (!jina || (str_cmp(val->tee[x], jina, len)
				&&	val->tee[x][len] == '='))
			{
				for (y = 0; val->tee[x][y]; y++)
				{
					buf[y] = val->tee[x][y];
					if (val->tee[x][y] == '=')
						break;
				}
				buf[y + 1] = '\0';
				buf_ext(buf, "'");
				buf_ext(buf, val->tee[x] + y + 1);
				buf_ext(buf, "'\n");
				_print(buf);
			}
			x++;
		} while (val->tee[x]);
	}

	return (0);
}
