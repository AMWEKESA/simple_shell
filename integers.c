#include "shell.h"

/**
 *int_str - converts a num to a string
 *
 * @num: num to be converten in an string
 * @string: buffer to save the num as string
 * @ch: ch to convert num
 *
 * Return: void
 */

void int_str(long num, char *string, int ch)
{
	int n = 0, i = 0;
	long cociente = num;
	char c[] = {"0123456789abcdef"};

	if (cociente == 0)
	{
		string[++n] = '0';
	}

	if (string[0] == '-')
	{
		i = 1;
	}

	do {
		if (cociente < 0)
		{
			string[++n] = c[-(cociente % ch)];
		}
		else
		{
			string[n++] = c[cociente % ch];
		}
		cociente /= ch;
	} while (cociente);

	if (i)
	{
		string[++n] = '-';
	}

	string[n] = '\0';
	str_rev(string);
}

/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 *
 * Return: int of string, else 0.
 */

int _atoi(char *s)
{
	int x = 1;
	unsigned int num = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			x *= -1;
		if (*s == '+')
			x *= +1;
		++s;
	}

	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		num = (num * 10) + (*s - '0');
		++s;
	}
	return (num * x);
}

/**
 * char_count - count character in string
 *
 * @string: pointer to str origen.
 * @ch: string with  chars to be counted
 *
 * Return: int of string, else 0.
 */

int char_count(char *string, char *ch)
{
	int x = 0, count = 0;

	while (string[x])
	{
		if (string[x] == ch[0])
			++count;
		++x;
	}
	return (count);
}
