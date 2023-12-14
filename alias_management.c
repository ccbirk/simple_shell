#include "shell.h"

/**
 * print_alias - it adds, remove or show aliases
 * @data: structure for the program data
 * @alias: name of the alias to be printed
 * Return: 0 if success, or other number if its declared in the arguments
 */
int print_alias(data_of_program *data, char *alias)
{
	int x, y, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_length(alias);
		for (x = 0; data->alias_list[x]; x++)
		{
			if (!alias || (str_compare(data->alias_list[x], alias, alias_length)
				&&	data->alias_list[x][alias_length] == '='))
			{
				for (x = 0; data->alias_list[x][y]; y++)
				{
					buffer[y] = data->alias_list[x][y];
					if (data->alias_list[x][y] == '=')
						break;
				}
				buffer[y + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[x] + y + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - this adds, remove or show aliases
 * @data: structure for the program data
 * @name: the name of the requested alias.
 * Return: 0 if success, or other number if its declared in the arguments
 */
char *get_alias(data_of_program *data, char *name)
{
	int z, alias_length;

	/* validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (z = 0; data->alias_list[z]; z++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_compare(name, data->alias_list[z], alias_length) &&
			data->alias_list[z][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[z] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - this adds, or override alias
 * @alias_string: alias to be set in the form (name='value')
 * @data: structure for the program data
 * Return: 0 if success, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, data_of_program *data)
{
	int p, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (p = 0; alias_string[p]; p++)
		if (alias_string[p] != '=')
			buffer[p] = alias_string[p];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + p + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; data->alias_list[j]; j++)
		if (str_compare(buffer, data->alias_list[j], p) &&
			data->alias_list[j][p] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->alias_list[j] = str_duplicate(alias_string);
	return (0);
}
