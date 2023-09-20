#include "shell.h"

/**
 * initial - initialize the struct with the info of the program
 *
 * @val: pointer to val
 * @argv: arguments of program
 * @argc: arguments count
 * @setting: environment pased to the program execution
 *
 * Return: void
 */

void initial(list *val, int argc, char *argv[], char **setting)
{
	int x = 0;

	val->process = argv[0];
	val->input_line = NULL;
	val->cmd = NULL;
	val->exec_counter = 0;

	if (argc == 1)
		val->file_descriptor = STDIN_FILENO;
	else
	{
		val->file_descriptor = open(argv[1], O_RDONLY);
		if (val->file_descriptor == -1)
		{
			print_out(val->process);
			print_out(": 0: Can't open ");
			print_out(argv[1]);
			print_out("\n");
			exit(127);
		}
	}
	val->tokens = NULL;
	val->setting = malloc(sizeof(char *) * 50);
	if (setting)
	{
		for (; setting[x]; x++)
		{
			val->setting[x] = str_dup(setting[x]);
		}
	}
	val->setting[x] = NULL;
	setting = val->setting;

	val->a_list = malloc(sizeof(char *) * 20);
	for (x = 0; x < 20; x++)
	{
		val->a_list[x] = NULL;
	}
}

/**
 * _ctrl_c - handle contro+c
 *
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 *
 * Return: void
 */

void _ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}
