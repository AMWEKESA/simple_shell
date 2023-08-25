# include "s_shell.h"

/**
 * logic_ops - checks fo logic operators (&& and ||)
 *
 * @x: index in the command being checked
 * @ops: array of logical operators for each previous command
 * @coms: pointer to  cammands array
 *
 * Return: x
 */

int logic_ops(char *coms[], int x, char ops[])
{
	char *ch = NULL;
	int y;

	y = 0;
	for (; coms[x] != NULL  && coms[x][y];)
	{
		if (coms[x][y] == '&' && coms[x][y + 1] == '&')
		{
			ch = coms[x];
			coms[x][y] = '\0';
			coms[x] = str_dup(coms[x]);
			coms[x + 1] = str_dup(ch + y + 2);
			++x;
			ops[x] = '&';
			free(ch);
			y = 0;
		}
		if (coms[x][y] == '|' && coms[x][y + 1] == '|')
		{
			ch = coms[x];
			coms[x][y] = '\0';
			coms[x] = str_dup(coms[x]);
			coms[x + 1] = str_dup(ch + y + 2);
			++x;
			ops[x] = '|';
			free(ch);
			y = 0;
		}
		 ++y;
	}
	return (x);
}

/**
*get_line - get line from prompt
*
* @val: pointer to val
*
* Return: succsess
*/

int get_line(list *val)
{
	static char *coms[10] = {NULL};
	size_t btys, x = 0;
	static char ops[10] = {'\0'};
	char buf[BUFFER_SIZE] = {'\0'};

	if (!coms[0] || (ops[0] == '&' && errno != 0) ||
		(ops[0] == '|' && errno == 0))
	{
		x = 0;
		do {

			free(coms[x]);
			coms[x] = NULL;
			++x;
		} while (coms[x]);

		btys = read(val->file_info, &buf, BUFFER_SIZE - 1);
		if (btys == 0)
			return (-1);

		x = 0;
		while (coms[x++])
		{
			coms[x] = str_dup(strtok(x ? NULL : buf, "\n;"));
			x = logic_ops(coms, x, ops);
		}
	}

	val->cur = coms[0];
	x = 0;
	for (; coms[x]; ++x)
	{
		coms[x] = coms[x + 1];
		ops[x] = ops[x + 1];
	}

	return (str_len(val->cur));
}