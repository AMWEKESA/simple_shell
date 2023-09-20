#include "shell.h"

/**
 * get_variable - gets the value of an environment variable
 *
 * @ind: the environment variable of interest
 * @val: pointer to val
 *
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */

char *get_variable(char *ind, list *val)
{
	int x;
	int var_len = 0;

	if (ind == NULL || val->setting == NULL)
		return (NULL);

	var_len = str_len(ind);

	x = 0;
	while (val->setting[x]);
	do {
		if (str_cmp(ind, val->setting[x], var_len) &&
		 val->setting[x][var_len] == '=')
		{
			return (val->setting[x] + var_len + 1);
		}
		++x;
	} while (val->setting[x]);

	return (NULL);
}

/**
 * set_variable - overwrite the value of the environment variable
 *
 * @ind: name of the variable to set
 * @value: new value
 * @val: pointer to val
 *
 * Return: 1 if NULL, 2 if there is an error, 0 if sucess.
 */

int set_variable(char *ind, char *value, list *val)
{
	int x, var_len = 0, new_var = 1;

	if (ind == NULL || value == NULL || val->setting == NULL)
		return (1);


	var_len = str_len(ind);

	x = 0;
	while (val->setting[x])
	{
		if (str_cmp(ind, val->setting[x], var_len) &&
		 val->setting[x][var_len] == '=')
		{
			new_var = 0;
			free(val->setting[x]);
			break;
		}
		x++;
	}
	val->setting[x] = str_con(str_dup(ind), "=");
	val->setting[x] = str_con(val->setting[x], value);

	if (new_var)
	{

		val->setting[x + 1] = NULL;
	}
	return (0);
}

/**
 * rem_variable - remove a ind from the environment
 *
 * @ind: the ind to remove
 * @val: pointer to val
 *
 * Return: 1 if removed, 0 if does not exist;
 */

int rem_variable(char *ind, list *val)
{
	int x, var_len = 0;

	if (ind == NULL || val->setting == NULL)
		return (0);

	var_len = str_len(ind);

	x = 0;
	while (val->setting[x])
	{
		if (str_cmp(ind, val->setting[x], var_len) &&
		 val->setting[x][var_len] == '=')
		{
			free(val->setting[x]);

			++x;
			for (; val->setting[x]; x++)
			{
				val->setting[x - 1] = val->setting[x];
			}
			val->setting[x - 1] = NULL;
			return (1);
		}
		x++;
	}

	return (0);
}


/**
 * print_variable - prints the current environ
 *
 * @val: pointer to val
 *
 * Return: void
 */

void print_variable(list *val)
{
	int j;

	for (j = 0; val->setting[j]; j++)
	{
		_print(val->setting[j]);
		_print("\n");
	}
}
