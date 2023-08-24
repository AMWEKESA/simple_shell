#include "s_shell.c"

/**
 * _print - writes chars in the stdout
 *
 * @str: pointer to array of chars
 *
 * Return: the number of bytes printed out
 */

int _print(char *str)
{
	return (write(STDOUT_FILENO, str, str_len(str)));
}

/**
 * printarr - writes a array of chars
 *
 * @str: pointer to array of chars
 *
 * Return: the number of bytes printed out
 */

int printarr(char *str)
{
	return (write(STDERR_FILENO, str, str_len(str)));
}

/**
 * print_err - writes out to standart error
 *
 * @val: a pointer to the program's val'
 * @err_code: error code to print
 *
 * Return: the number of bytes printed out
 */

int print_err(int err_code, list *val)
{
	char n[10] = {'\0'};

	str_long((long) val->count, n, 10);

	if (err_code == 2 || err_code == 3)
	{
		printarr(val->p_name);
		printarr(": ");
		printarr(n);
		printarr(": ");
		printarr(val->tok[0]);
		if (err_code == 2)
			printarr(": Illegal number: ");
		else
			printarr(": can't cd to ");
		printarr(val->tok[1]);
		printarr("\n");
	}
	else if (err_code == 127)
	{
		printarr(val->p_name);
		printarr(": ");
		printarr(n);
		printarr(": ");
		printarr(val->cmd_name);
		printarr(": not found\n");
	}
	else if (err_code == 126)
	{
		printarr(val->p_name);
		printarr(": ");
		printarr(n);
		printarr(": ");
		printarr(val->cmd_name);
		printarr(": Permission denied\n");
	}
	return (0);
}

/**
 * _atoi - convert a string to an integer..
 *
 * @s: pointer to str origen
 *
 * Return: int of string, else 0
 */

int _atoi(char *s)
{
	int i = 1;
	unsigned int n = 0;

	do {
		if (*s == '-')
			i *= -1;
		if (*s == '+')
			i *= +1;
		s++;
	} while (!('0' <= *s && *s <= '9') && *s != '\0');

	for (; '0' <= *s && *s <= '9' && *s != '\0'; ++s)
	{
		n = (n * 10) + (*s - '0');
	}
	return (n * i);
}
