#include "s_shell.h"

/**
 * exc - execute a command
 *
 * @val: a pointer to val
 *
 * Return: zero if successful, else -1.
 */

int exc(list *val)
{
	int point = 0;
	int state;
	pid_t pid;

	point = predef(val);
	if (point != -1)
		return (point);

	point = find_process(val);
	if (point)
	{
		return (point);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror(val->cmd_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			point = execve(val->tok[0], val->tok, val->env);
			if (point == -1)
				perror(val->cmd_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&state);
			if (WIFEXITED(state))
				errno = WEXITSTATUS(state);
			else if (WIFSIGNALED(state))
				errno = 128 + WTERMSIG(state);
		}
	}
	return (0);
}
