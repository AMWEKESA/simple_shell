#include "shell.h"
/**
 * set_working_dir - set the work directory
 *
 * @val: pointer to val
 * @new_dir: path to be set as work directory
 *
 * Return: success
 */

int set_working_dir(list *val, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_cmp(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		set_variable("PWD", new_dir, val);
	}
	set_variable("OLDPWD", old_dir, val);
	return (0);
}
