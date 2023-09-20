#include "shell.h"

/**
 * show_prompt - infinite loop that prints the prompt
 *
 * @prompt: prompt to be printed
 * @val: pointer to val
 *
 * Return: void
 */

void show_prompt(char *prompt, list *val)
{
	int err_code = 0;
	int string_len = 0;

	for (val->exec_counter = 1; ; ++(val->exec_counter))
	{
		_print(prompt);
		err_code = string_len = get_line(val);

		if (err_code == EOF)
		{
			free_space(val);
			exit(errno);
		}
		if (string_len >= 1)
		{
			process_more(val);
			process_variables(val);
			separate_String(val);
			if (val->tokens[0])
			{
				err_code = execute(val);
				if (err_code != 0)
					print_err(err_code, val);
			}
			free_repeat(val);
		}
	}
}
