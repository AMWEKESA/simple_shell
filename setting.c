#include "shell.h"

/**
 * show_setting - shows the environment setting where the shell runs
 *
 * @val: struct for the program's val
 *
 * Return: success
 */

int show_setting(list *val)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;

	if (val->tokens[1] == NULL)
		print_variable(val);
	else
	{
		for (i = 0; val->tokens[1][i]; ++i)
		{
			if (val->tokens[1][i] == '=')
			{
				var_copy = str_dup(get_variable(cpname, val));
				if (var_copy != NULL)
					set_variable(cpname, val->tokens[1] + i + 1, val);

				print_variable(val);
				if (get_variable(cpname, val) == NULL)
				{
					_print(val->tokens[1]);
					_print("\n");
				}
				else
				{
					set_variable(cpname, var_copy, val);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = val->tokens[1][i];
		}
		errno = 2;
		perror(val->cmd);
		errno = 127;
	}
	return (0);
}

/**
 * get_setting - get environment
 *
 * @val: struct for the program's val
 *
 * Return: success
 */

int get_setting(list *val)
{
	if (val->tokens[1] == NULL || val->tokens[2] == NULL)
		return (0);
	if (val->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(val->cmd);
		return (5);
	}

	set_variable(val->tokens[1], val->tokens[2], val);

	return (0);
}

/**
 * rem_setting - rem. the environment setting
 *
 * @val: struct for the program's val'
 *
 * Return: ..
 */

int rem_setting(list *val)
{
	if (val->tokens[1] == NULL)
		return (0);
	if (val->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(val->cmd);
		return (5);
	}
	rem_variable(val->tokens[1], val);

	return (0);
}

/**
* get_line - read one line from the prompt
*
* @val: pointer to val
*
* Return: number of bytes
*/

int get_line(list *val)
{
	char mem[BUFFER_SIZE] = {'\0'};
	static char *cmds[10] = {NULL}, ops[10] = {'\0'};
	ssize_t ch, i = 0;

	if (!cmds[0] || (ops[0] == '&' && errno != 0) ||
		(ops[0] == '|' && errno == 0))
	{
		i = 0;
		while (cmds[i])
		{
			free(cmds[i]);
			cmds[i] = NULL;
			++i;
		}

		ch = read(val->file_descriptor, &mem, BUFFER_SIZE - 1);
		if (ch == 0)
			return (-1);

		i = 0;
		while (cmds[++i])
		{
			cmds[i] = str_dup(str_tok(i ? NULL : mem, "\n;"));
			i = logic_operation(cmds, i, ops);
		}
	}

	val->input_line = cmds[0];
	i = 0;
	while (cmds[i])
	{
		cmds[i] = cmds[i + 1];
		ops[i] = ops[i + 1];
		++i;
	}
	return (str_len(val->input_line));
}


/**
* logic_operation - checks for and split  &&, || operators
*
* @cmds: array of the commands.
* @i: index of commands to be checked
* @ops: array of the logical operators
*
* Return: index of the last command
*/

int logic_operation(char *cmds[], int i, char ops[])
{
	char *sub = NULL;
	int j;

	j = 0;
	while (cmds[i] != NULL  && cmds[i][j])
	{
		if (cmds[i][j] == '&' && cmds[i][j + 1] == '&')
		{

			sub = cmds[i];
			cmds[i][j] = '\0';
			cmds[i] = str_dup(cmds[i]);
			cmds[i + 1] = str_dup(sub + j + 2);
			i++;
			ops[i] = '&';
			free(sub);
			j = 0;
		}
		if (cmds[i][j] == '|' && cmds[i][j + 1] == '|')
		{

			sub = cmds[i];
			cmds[i][j] = '\0';
			cmds[i] = str_dup(cmds[i]);
			cmds[i + 1] = str_dup(sub + j + 2);
			i++;
			ops[i] = '|';
			free(sub);
			j = 0;
		}
		++j;
	}
	return (i);
}
