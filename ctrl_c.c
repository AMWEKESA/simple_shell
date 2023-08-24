#include "s_shell.h"

/**
 * ctrl_c - A function that handles ctrl_c
 *
 * @signal_number: The signal number
 * Return: void
 */

void ctrl_c(int signal_number __attribute__((unused)))
{
	_print("\n" P_MSG);
}
