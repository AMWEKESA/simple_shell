#include "shell.h"

/**
 * terminate - exit of the program with the status
 * 
 * @val: pointer to val
 * 
 * Return: success
 */

int terminate(list *val)
{
	int x;

	if (val->tokens[1] != NULL)
	{
		for (x = 0; val->tokens[1][x]; x++)
			if ((val->tokens[1][x] < '0' || val->tokens[1][x] > '9')
				&& val->tokens[1][x] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(val->tokens[1]);
	}
	free_space(val);
	exit(errno);
}
