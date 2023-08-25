#include "s_shell.h"

/**
 *str_len - gets  the length of a string.
 *
 * @str: pointer to str
 *
 * Return: length of str.
 */

int str_len(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (str[len] != '\0')
	{
		len++;

	}
	return (len);
}

/**
 * str_dup - duplicates an str
 *
 * @str: str to be copied
 * Return: pointer to str array
 */

char *str_dup(char *str)
{
	char *out;
	int len;
	int x;

	if (str == NULL)
		return (NULL);

	len = str_len(str) + 1;

	out = malloc(sizeof(char) * len);

	if (out == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	x = 0;
	while (x < len)
	{
		out[x] = str[x];
		++x;
	}

	return (out);
}

/**
 * str_cmp - Compare two strs
 *
 * @str1: str one to compare to str2
 * @str2: str two, to compare to str1
 * @num: number of characters to be compared
 * Return: 1 if equal,else 0
 */

int str_cmp(char *str1, char *str2, int num)
{
	int i;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (num == 0)
	{
		if (str_len(str1) != str_len(str2))
			return (0);
		for (i = 0; str1[i]; i++)
		{
			if (str1[i] != str2[i])
				return (0);
		}
		return (1);
	}
	else
	{
		for (i = 0; i < num ; i++)
		{
			if (str1[i] != str2[i])
			return (0);
		}
		return (1);
	}
}

/**
 * str_con- concatenates two strs
 *
 * @str1: str to be concatenated with str2
 * @str2: str to be concatenated with str1
 *
 * Return: pointer to the array
 */

char *str_con(char *str1, char *str2)
{
	char *output;
	int length1 = 0, length2 = 0;

	if (str1 == NULL)
		str1 = "";
	length1 = str_len(str1);

	if (str2 == NULL)
		str2 = "";
	length2 = str_len(str2);

	output = malloc(sizeof(char) * (length1 + length2 + 1));
	if (output == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (length1 = 0; str1[length1] != '\0'; length1++)
		output[length1] = str1[length1];
	free(str1);

	for (length2 = 0; str2[length2] != '\0'; length2++)
	{
		output[length1] = str2[length2];
		length1++;
	}

	output[length1] = '\0';
	return (output);
}


/**
 *str_rev - reverses a str.
 *
 * @str: pointer to str.
 *
 * Return: void.
 */

void str_rev(char *str)
{

	int x;
	int len;
	char c;

	len = str_len(str) - 1;
	x = 0;

	while (x < len)
	{
		c = str[x];
		str[x++] = str[len];
		str[len--] = c;
	}
}
