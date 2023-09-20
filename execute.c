#include "shell.h"

/**
 * execute - execute a command with its entire path variables
 *
 * @val: pointer to val
 * Return: 0 on sucess, else -1.
 */

int execute(list *val)
{
	int s = 0;
	int steate;
	pid_t pidd;

	s = check_predefined(val);
	if (s != -1)
		return (s);

	s = find_program(val);
	if (s)
	{
		return (s);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(val->cmd);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			s = execve(val->tokens[0], val->tokens, val->setting);
			if (s == -1)
				perror(val->cmd), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&steate);
			if (WIFEXITED(steate))
				errno = WEXITSTATUS(steate);
			else if (WIFSIGNALED(steate))
				errno = 128 + WTERMSIG(steate);
		}
	}
	return (0);
}
