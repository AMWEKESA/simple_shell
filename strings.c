#include "shell.h"

/**
 * str_len - gets the length of a string
 *
 * @string: pointer to string
 *
 * Return: len of string
 */

int str_len(char *string)
{
	int len = 0;

	if (string == NULL)
		return (0);

	while (string[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * str_dup - duplicates a string
 *
 * @string: String to be copied
 *
 * Return: pointer to the array
 */

char *str_dup(char *string)
{
	char *copy;
	int len, i;

	if (string == NULL)
		return (NULL);

	len = str_len(string) + 1;

	copy = malloc(sizeof(char) * len);

	if (copy == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; ++i)
	{
		copy[i] = string[i];
	}

	return (copy);
}

/**
 * str_cmp - Compares two strings
 *
 * @str1: string to compare with str2
 * @str2: string to compare with str1
 * @num: number of characters to be compared
 *
 * Return: 1 if the strings are equal, else 0
 */

int str_cmp(char *str1, char *str2, int num)
{
	int c;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (num == 0)
	{
		if (str_len(str1) != str_len(str2))
			return (0);

		for (c = 0; str1[c]; c++)
		{
			if (str1[c] != str2[c])
				return (0);
		}
		return (1);
	}
	else
	{
		for (c = 0; c < num ; c++)
		{
			if (str1[c] != str2[c])
			return (0);
		}
		return (1);
	}
}

/**
 * str_con - concatenates two strings
 *
 * @str1: String to be concatenated with str2
 * @str2: String to be concatenated with str1
 *
 * Return: pointer to the array
 */

char *str_con(char *str1, char *str2)
{
	char *res;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = str_len(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = str_len(str2);

	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (; str1[len1] != '\0'; len1++)
		res[len1] = str1[len1];
	free(str1);

	for (; str2[len2] != '\0'; len2++)
	{
		res[len1] = str2[len2];
		len1++;
	}

	res[len1] = '\0';
	return (res);
}


/**
 * str_rev - reverses a string
 *
 * @string: pointer to string
 *
 * Return: void.
 */

void str_rev(char *string)
{

	int i = 0, len = str_len(string) - 1;
	char ch;

	while (i < len)
	{
		ch = string[i];
		string[++i] = string[len];
		string[len--] = ch;
	}
}
