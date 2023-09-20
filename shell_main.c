#include "shell.h"
/**
 * main - initialize the variables of the program
 *
 * @argc: arguement counter
 * @argv: arguments received from the command line
 * @setting: number of values received from the command line
 *
 * Return: zero on succes
 */

int main(int argc, char *argv[], char *setting[])
{
	list val_struct = {NULL}, *val = &val_struct;
	char *prompt = "";

	initial(val, argc, argv, setting);

	signal(SIGINT, _ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	show_prompt(prompt, val);
	return (0);
}
