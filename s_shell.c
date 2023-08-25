#include "s_shell.h"

/**
 * main - main function of the program
 *
 * @argc: argument counter
 * @argv: argument vector
 * @env: number of args received from the command line
 *
 * Return: 0 on succes.
 */

int main(int argc, char *argv[], char *env[])
{
	list prog_struct = {NULL}, *val = &prog_struct;
	char *prompt = "";

	init_val(val, argc, argv, env);

	signal(SIGINT, ctrl_c);

	if (isatty(STDIN_FILENO))
	{
		if (isatty(STDOUT_FILENO))
		{
			if (argc == 1)
			{
				errno = 2;
				prompt = P_MSG;
			}
		}
	}

	errno = 0;
	err(prompt, val);
	return (0);
}

/**
  * ctrl_c - A function that handles ctrl_c
  *
  * signal_number: signal number
  * Return: void
  */

void ctrl_c(int signal_number __attribute__((unused)))
{
	_print("\n" P_MSG);
}
