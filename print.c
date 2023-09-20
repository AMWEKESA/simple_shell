#include "shell.h"

/**
 * _print - writes chars to std output
 *
 * @string: pointer to chars
 *
 * Return: number of bytes printed out
 */

int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_len(string)));
}

/**
 * print_out - writes chars to stderror
 *
 * @string: pointer to the array of chars
 *
 * Return: number of bytes printed outpointer to
 */

int print_out(char *string)
{
	return (write(STDERR_FILENO, string, str_len(string)));
}

/**
 * print_err - writes to char std error
 *
 * @val: pointer to val
 *
 * @errorcode: error code to print
 *
 * Return: number of bytes printed out
 */

int print_err(int errorcode, list *val)
{
	char n_as_string[10] = {'\0'};

	int_str((long) val->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		print_out(val->process);
		print_out(": ");
		print_out(n_as_string);
		print_out(": ");
		print_out(val->tokens[0]);
		if (errorcode == 2)
			print_out(": Illegal num: ");
		else
			print_out(": can't cd to ");
		print_out(val->tokens[1]);
		print_out("\n");
	}
	else if (errorcode == 127)
	{
		print_out(val->process);
		print_out(": ");
		print_out(n_as_string);
		print_out(": ");
		print_out(val->cmd);
		print_out(": not found\n");
	}
	else if (errorcode == 126)
	{
		print_out(val->process);
		print_out(": ");
		print_out(n_as_string);
		print_out(": ");
		print_out(val->cmd);
		print_out(": Permission denied\n");
	}
	return (0);
}
