#include "shell.h"

/**
 * expand_variables - it will expand vars
 * @data: a pointer to a structure of the program data
 *
 * Return: nothing, but sets errno.
 */
void expand_variables(data_of_program *data)
{
	int y, z;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (y = 0; line[y]; y++)
		if (line[y] == '#')
			line[y--] = '\0';
		else if (line[y] == '$' && line[y + 1] == '?')
		{
			line[y] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + y + 2);
		}
		else if (line[y] == '$' && line[y + 1] == '$')
		{
			line[y] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + y + 2);
		}
		else if (line[y] == '$' && (line[y + 1] == ' ' || line[y + 1] == '\0'))
			continue;
		else if (line[y] == '$')
		{
			for (z = 1; line[y + z] && line[y + z] != ' '; z++)
				expansion[z - 1] = line[y + z];
			temp = env_get_key(expansion, data);
			line[y] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + y + z);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - expands alias.
 * @data: a pointer to a structure of the program data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(data_of_program *data)
{
	int i, g, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (g = 0; line[i + g] && line[i + g] != ' '; g++)
			expansion[g] = line[i + g];
		expansion[g] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + i + g);
			line[i] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - this appends str at end of the buffer
 * @buffer: the buffer to be filled.
 * @str_to_add: str to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length, n;

	length = str_length(buffer);
	for (n = 0; str_to_add[n]; n++)
	{
		buffer[length + n] = str_to_add[n];
	}
	buffer[length + n] = '\0';
	return (length + n);
}
