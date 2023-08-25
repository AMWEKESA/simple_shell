#include "s_shell.h"

/**
 * replace - expands process
 *
 * @val: a pointer to val
 *
 * Return: void
 */
void replace(list *val)
{
	int x = 0, y = 0;
	char *sub;
	int ext = 0;
	char com[BUFFER_SIZE] = {0};
	char length[BUFFER_SIZE] = {'\0'};

	if (val->cur == NULL)
		return;

	buf_ext(com, val->cur);

	do {
		while (com[x + y] && com[x + y] != ' ')
		{
			length[y] = com[x + y];
			++y;
		}
		length[y] = '\0';

		sub = gel(val, length);
		if (sub)
		{
			length[0] = '\0';
			buf_ext(length, com + x + y);
			com[x] = '\0';
			buf_ext(com, sub);
			com[str_len(com)] = '\0';
			buf_ext(com, length);
			ext = 1;
		} while (com[x]);
		x += y + 1;
	} while (com[x]);
	if (ext)
	{
		free(val->cur);
		val->cur = str_dup(com);
	}
}


/**
 * processvar - expand variables
 *
 * @val: a pointer to val
 *
 * Return: nothing, but sets errno.
 */

void processvar(list *val)
{
	int x, y;
	char cmd[BUFFER_SIZE];
	char length[BUFFER_SIZE] = {'\0'}, *sub;

	if (val->cur == NULL)
		return;
	buf_ext(cmd, val->cur);
	for (x = 0; cmd[x]; x++)
	{
		if (cmd[x] == '#')
			cmd[x--] = '\0';
			break;
		else if (cmd[x] == '$' && cmd[x + 1] == '?')
		{
			cmd[x] = '\0';
			str_long(errno, length, 10);
			buf_ext(cmd, length);
			buf_ext(cmd, val->cur + x + 2);
		}
		else if (cmd[x] == '$' && cmd[x + 1] == '$')
		{
			cmd[x] = '\0';
			str_long(getpid(), length, 10);
			buf_ext(cmd, length);
			buf_ext(cmd, val->cur + x + 2);
		}
		else if (cmd[x] == '$' && (cmd[x + 1] == ' ' || cmd[x + 1] == '\0'))
			continue;
		else if (cmd[x] == '$')
		{
			for (y = 1; cmd[x + y] && cmd[x + y] != ' '; y++)
				length[y - 1] = cmd[x + y];
			sub = env_key(length, val);
			cmd[x] = '\0', length[0] = '\0';
			buf_ext(length, cmd + x + y);
			sub ? buf_ext(cmd, sub) : 1;
			buf_ext(cmd, length);
		}
	}
	if (!str_cmp(val->cur, cmd, 0))
		free(val->cur);
		val->cur = str_dup(cmd);
}


/**
 * buf_ext - append string to buffer
 *
 * @buf: buffer to be filled
 * @strconc: string to be concatenated in the buffer
 * Return: nothing, but sets errno.
 */

int buf_ext(char *buf, char *strconc)
{
	int len;
	int x;

	len = str_len(buf);
	for (x = 0; strconc[x]; x++)
	{
		buf[len + x] = strconc[x];
	}
	buf[len + x] = '\0';
	return (len + x);
}
