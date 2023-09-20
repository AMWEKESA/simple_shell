#include "shell.h"

/**
 * process_variables - proce variables
 *
 * @val: a pointer to a struct of the program's val
 *
 * Return: nothing, but sets errno.
 */

void process_variables(list *val)
{
	int x, y;
	char ch[BUFFER_SIZE] = {0}, a[BUFFER_SIZE] = {'\0'}, *sub;

	if (val->input_line == NULL)
		return;
	append(ch, val->input_line);
	for (x = 0; ch[x]; ++x)
		if (ch[x] == '#')
			ch[x--] = '\0';
		else if (ch[x] == '$' && ch[x + 1] == '?')
		{
			ch[x] = '\0';
			int_str(errno, a, 10);
			append(ch, a);
			append(ch, val->input_line + x + 2);
		}
		else if (ch[x] == '$' && ch[x + 1] == '$')
		{
			ch[x] = '\0';
			int_str(getpid(), a, 10);
			append(ch, a);
			append(ch, val->input_line + x + 2);
		}
		else if (ch[x] == '$' && (ch[x + 1] == ' ' || ch[x + 1] == '\0'))
			continue;
		else if (ch[x] == '$')
		{
			for (y = 1; ch[x + y] && ch[x + y] != ' '; ++y)
				a[y - 1] = ch[x + y];
			sub = get_variable(a, val);
			ch[x] = '\0', a[0] = '\0';
			append(a, ch + x + y);
			sub ? append(ch, sub) : 1;
			append(ch, a);
		}
	if (!str_cmp(val->input_line, ch, 0))
	{
		free(val->input_line);
		val->input_line = str_dup(ch);
	}
}

/**
 * process_more - expands aliases
 *
 * @val: a pointer to a struct of the program's val
 *
 * Return: nothing, but sets errno.
 */

void process_more(list *val)
{
	int x, y;
	int new_size = 0;
	char ch[BUFFER_SIZE] = {0}, a[BUFFER_SIZE] = {'\0'};
	char *sub;

	if (val->input_line == NULL)
		return;

	append(ch, val->input_line);

	for (x = 0; ch[x]; ++x)
	{
		for (y = 0; ch[x + y] && ch[x + y] != ' '; ++y)
			a[y] = ch[x + y];
		a[y] = '\0';

		sub = show_alias(val, a);
		if (sub)
		{
			a[0] = '\0';
			append(a, ch + x + y);
			ch[x] = '\0';
			append(ch, sub);
			ch[str_len(ch)] = '\0';
			append(ch, a);
			new_size = 1;
		}
		break;
	}
	if (new_size)
	{
		free(val->input_line);
		val->input_line = str_dup(ch);
	}
}
