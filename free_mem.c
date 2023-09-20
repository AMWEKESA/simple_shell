#include "shell.h"

/**
 * free_repeat - free the fields needed each loop
 * 
 * @val: pointer to val
 * 
 * Return: void
 */

void free_repeat(list *val)
{
	if (val->tokens)
		free_pointer(val->tokens);
	if (val->input_line)
		free(val->input_line);
	if (val->cmd)
		free(val->cmd);

	val->input_line = NULL;
	val->cmd = NULL;
	val->tokens = NULL;
}

/**
 * free_space - free all field of the val
 * 
 * @val: pointer to val
 * 
 * Return: void
 */

void free_space(list *val)
{
	if (val->file_descriptor != 0)
	{
		if (close(val->file_descriptor))
			perror(val->process);
	}
	free_repeat(val);
	free_pointer(val->setting);
	free_pointer(val->a_list);
}

/**
 * free_pointer - frees each pointer of an array of pointers
 *
 * @arr: array of pointers
 * 
 * Return: void
 */
void free_pointer(char **arr)
{
	int i;

	if (arr != NULL)
	{
		for (i = 0; arr[i]; i++)
			free(arr[i]);

		free(arr);
		arr = NULL;
	}
}
