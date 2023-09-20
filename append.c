#include "shell.h"

/**
 * append - append string at end of the buffer
 *
 * @buffer: buffer to be filled
 * @src_str: string to be copied in the buffer
 *
 * Return: void and sets errno
 */

int append(char *buffer, char *src_str)
{
	int len, x;

	len = str_len(buffer);

	x = 0;
	while (src_str[x])
	{
		buffer[len + x] = src_str[x];
		 ++x;
	}
	buffer[len + x] = '\0';
	return (len + x);
}
