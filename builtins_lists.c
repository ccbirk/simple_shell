#include "shell.h"

/**
 * builtins_list - searches for match and executes the associated builtin
 * @data: structure for the program data
 * Return: the return of the funct executed if there is a match.
 * or else returns -1.
 **/
int builtins_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
/*if there is a match between the given command and a builtin,*/
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
/*executes the function, and return the return value of the function*/
			return (options[iterator].function(data));
		}
/*if there is no match returns -1 */
	}
	return (-1);
}
