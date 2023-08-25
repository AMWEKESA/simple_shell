#include "s_shell.c"

/**
 * str_long - converts a number to a string.
 * @num: number to be converten in an string.
 * @str: buffer to save the number as string.
 * @base: base to convert number
 *
 * Return: void.
 */
void str_long(long num, char *str, int base)
{
	int i = 0;
	int neg = 0;
	long n = num;
	char c[] = {"0123456789abcdef"};

	if (n == 0)
		str[i++] = '0';

	if (str[0] == '-')
		neg = 1;

	for (; n != 0; n /= base)
	{
		if (n < 0)
			str[i++] = c[-(n % base)];
		else
			str[i++] = c[n % base];
		n /= base;
	}
	if (neg)
		str[i++] = '-';

	str[i] = '\0';
	str_rev(str);
}

/**
* char_count - count the insidents of a character in string
*
* @str: pointer to str
* @c: string with  chars to be counted
*
* Return: int of string or 0
*/

int char_count(char *str, char *c)
{
	int i = 0;
	int count = 0;

	for (; str[i]; i++)
	{
		if (str[i] == c[0])
			count++;
	}
	return (count);
}