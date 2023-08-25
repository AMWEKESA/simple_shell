#include "s_shell.h"

/**
 * init_val - program initialization
 *
 * @val: pointer to val
 * @argc: argument counter
 * @argv: arguments vector pased to the process
 * @env: environment of program
 *
 * Return: void
 */

void init_val(list *val, int argc, char *argv[], char **env)
{
	int x = 0;

	val->p_name = argv[0];
	val->count = 0;
	val->cur = NULL;
	val->cmd_name = NULL;
	if (argc == 1)
		val->file_info = STDIN_FILENO;
	else
	{
		val->file_info = open(argv[1], O_RDONLY);
		if (val->file_info == -1)
		{
			printarr(val->p_name);
			printarr(": 0: Can't open ");
			printarr(argv[1]);
			printarr("\n");
			exit(127);
		}
	}
	val->tok = NULL;
	val->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		x = 0;
		do {
			val->env[x] = str_dup(env[x]);
			++x;
		} while (env[x]);
	}

	val->env[x] = NULL;
	env = val->env;
	val->tee = malloc(sizeof(char *) * 20);

	x = 0;
	do {
		val->tee[x] = NULL;
		++x;
	} while (x < 20);
}


/**
 *err - loop for prompt
 *
 * @prompt: prompt msg
 * @val: pointer to list
 *
 * Return - void
 */

void err(char *prompt, list *val)
{
	int err = 0;
	int len;

	do {
		_print(prompt);
		err = len = get_line(val);

		if (err == EOF)
		{
			free_val(val);
			exit(errno);
		}
		if (len >= 1)
		{
			replace(val);
			processvar(val);
			strtoken(val);

			if (val->tok[0])
			{
				err = exc(val);

				if (err != 0)
					print_err(err, val);
			}
			free_repeat(val);
		}
	} while (++(val->count));
}
