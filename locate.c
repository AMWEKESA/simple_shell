#include "s_shell.h"

/**
 * find_process - find a program in path
 * @val: a pointer to the program's val
 *
 * Return: 0 on success, else error code
 */

int find_process(list *val)
{
	int x = 0, err_code = 0;
	char **folders;

	if (!val->cmd_name)
		return (2);

	if (val->cmd_name[0] == '/' || val->cmd_name[0] == '.')
		return (inspect_file(val->cmd_name));

	free(val->tok[0]);
	val->tok[0] = str_con(str_dup("/"), val->cmd_name);
	if (!val->tok[0])
		return (2);

	folders = locate(val);

	if (!folders || !folders[0])
	{
		errno = 127;
		return (127);
	}
	x = 0;
	while (folders[x])
	{
		folders[x] = str_con(folders[x], val->tok[0]);
		err_code = inspect_file(folders[x]);
		if (err_code == 0 || err_code == 126)
		{
			errno = 0;
			free(val->tok[0]);
			val->tok[0] = str_dup(folders[x]);
			free_pointer(folders);
			return (err_code);
		}
		++x;
	}
	free(val->tok[0]);
	val->tok[0] = NULL;
	free_pointer(folders);
	return (err_code);
}

/**
 * locate - tokenize the path in directories
 * @val: a pointer to the program's val
 * Return: array of path directories
 */

char **locate(list *val)
{
	int x = 0;
	int folder_count = 2;
	char **tok = NULL;
	char *PATH;

	PATH = env_key("PATH", val);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = str_dup(PATH);

	for (x = 0; PATH[x]; x++)
	{
		if (PATH[x] == ':')
		folder_count++;
	}

	tok = malloc(sizeof(char *) * folder_count);

	x = 0;
	tok[x] = str_dup(strtok(PATH, ":"));
	for (; tok[x]; ++x)
	{
		tok[x] = str_dup(strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tok);

}

/**
 * inspect_file - checks for file existance
 *
 * @ c: pointer to file name
 *
 * Return: 0 on success, or error code if it exists.
 */

int inspect_file(char *c)
{
	struct stat f;

	if (stat(c, &f) != -1)
	{
		if (S_ISDIR(f.st_mode) ||  access(c, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
