#include "s_shell.c"

int buf_ext(char *buf, char *strconc);
/**
 * printenv - prints the current environment
 *
 * @val: struct for the program's data
 * Return: void
 */

void printenv(list *val)
{
	int j;

	for (j = 0; val->env[j]; j++)
	{
		_print(val->env[j]);
		_print("\n");
	}
}

/**
 * key- overwrite the id of the environment variable
 *
 * @ind: variable to be set
 * @id: new id
 * @val: pointer to val
 *
 * Return: always
 */

int key(char *ind, char *id, list *val)
{
	int i, ind_len = 0, new_ind = 1;

	 if (ind == NULL || id == NULL || val->env == NULL)
		return (1);

	ind_len = str_len(ind);

	for (i = 0; val->env[i]; i++)
	{
		if (str_cmp(ind, val->env[i], ind_len) &&
		 val->env[i][ind_len] == '=')
		{
			new_ind = 0;
			free(val->env[i]);
			break;
		}
	}
	val->env[i] = str_con(str_dup(ind), "=");
	val->env[i] = str_con(val->env[i], id);

	if (new_ind)
	{
		val->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * rm_env - remove an ind from the environment
 *
 * @ind: the ind to be removed
 * @val: pointer val
 *
 * Return: 1 is removed, else 0
 */
int rm_env(char *ind, list *val)
{
	int i, ind_len = 0;

	if (ind == NULL || val->env == NULL)
		return (0);

	ind_len = str_len(ind);

	for (i = 0; val->env[i]; i++)
	{
		if (str_cmp(ind, val->env[i], ind_len) &&
		 val->env[i][ind_len] == '=')
		{
			free(val->env[i]);

			++i;
			while (val->env[i])
			{
				val->env[i - 1] = val->env[i];
				++i;
			}

			val->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * env_key - gets the id of environment
 *
 * @ind: environment index of interest
 * @val: pointer to val
 *
 * Return: pointer to the inex of the variable, else NULL
 */
char *env_key(char *ind, list *val)
{
	int i, ind_len = 0;

	if (ind == NULL || val->env == NULL)
		return (NULL);

	ind_len = str_len(ind);

	i = 0;
	do {
		if (str_cmp(ind, val->env[i], ind_len) &&
		 val->env[i][ind_len] == '=')
		{
			return (val->env[i] + ind_len + 1);
		}
		++i;
	} while (val->env[i]);
	return (NULL);
}