#include "shell.h"

int find_file(char *full_path);

/**
 * find_program - find a program in path
 *
 * @val: a pointer to the program's val
 *
 * Return: 0 on success, else error code
 */

int find_program(list *val)
{
	int i = 0, ret_code = 0;
	char **dir;

	if (!val->cmd)
		return (2);

	if (val->cmd[0] == '/' || val->cmd[0] == '.')
		return (find_file(val->cmd));

	free(val->tokens[0]);
	val->tokens[0] = str_con(str_dup("/"), val->cmd);
	if (!val->tokens[0])
		return (2);

	dir = route(val);

	if (!dir || !dir[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dir[i]; i++)
	{
		dir[i] = str_con(dir[i], val->tokens[0]);
		ret_code = find_file(dir[i]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(val->tokens[0]);
			val->tokens[0] = str_dup(dir[i]);
			free_pointer(dir);
			return (ret_code);
		}
	}
	free(val->tokens[0]);
	val->tokens[0] = NULL;
	free_pointer(dir);
	return (ret_code);
}

/**
 * route - tokenize the path in dir
 * 
 * @val: a pointer to the program's val
 * 
 * Return: array of path dir
 */

char **route(list *val)
{
	int i = 0;
	int dir_count = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = get_variable("PATH", val);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_dup(PATH);

	i = 0;
	while (PATH[i])
	{
		if (PATH[i] == ':')
			dir_count++;
		i++;
	}

	tokens = malloc(sizeof(char *) * dir_count);

	i = 0;
	tokens[i] = str_dup(str_tok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = str_dup(str_tok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * find_file - checks if exists a file
 *
 * @full_path: pointer to the full file name
 *
 * Return: 0, or error code
 */

int find_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
