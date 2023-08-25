#include "s_shell.h"

/**
 * free_repeat - free recussive process
 *
 * @val: pointer to  val
 *
 * Return: void
 */

void free_repeat(list *val)
{
	if (val->tok)
	{
		free(val->tok);
	}

	if (val->cur)
	{
		free(val->cur);
	}

	if (val->cmd_name)
	{
		free(val->cmd_name);
	}

	val->cur = NULL;
	val->cmd_name = NULL;
	val->tok = NULL;
}

/**
 * free_val - free all field of the val
 *
 * @val: poiner of val
 *
 * Return: void
 */

void free_val(list *val)
{
	if (val->file_info != 0)
	{
		if (close(val->file_info))
			perror(val->p_name);
	}
	free_repeat(val);
	free_pointer(val->env);
	free_pointer(val->tee);
}

/**
 * free_pointer - frees each pointer
 *
 * @array: array of pointers
 *
 * Return: void
 */

void free_pointer(char **array)
{
	int x;

	if (array != NULL)
	{
		x = 0;
		do {
			free(array[x]);
			++x;
		} while (array[x]);

		free(array);
		array = NULL;
	}
}
