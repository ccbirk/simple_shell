#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - find a program in the path.
 * @data: pointer to the program data
 * Return: 0 if success, errcode otherwise
 */

int find_program(data_of_program *data)
{
	int z = 0, ret_code = 0;
	char **directories;

	if (!data->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	directories = tokenize_path(data);/* search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (z = 0; directories[z]; z++)
	{/* appends the function_name to path */
		directories[z] = str_concat(directories[z], data->tokens[0]);
		ret_code = check_file(directories[z]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(directories[z]);
			free_array_of_pointers(directories);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(directories);
	return (ret_code);
}

/**
 * tokenize_path - tokenize the path in dirs.
 * @data: a pointer to the program data
 * Return: array of path dirs
 */

char **tokenize_path(data_of_program *data)
{
	int x = 0;
	int counter_directories = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* find the number of directories in the PATH */
	for (x = 0; PATH[x]; x++)
	{
		if (PATH[x] == ':')
			counter_directories++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * counter_directories);

	/*tokenize and duplicate each token of path*/
	x = 0;
	tokens[x] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[x++])
	{
		tokens[x] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - checks if a file exists, if it is not a dir and
 * if it has executable permisions for permisions.
 * @full_path: pointer to the full fname
 * Return: 0 on success, or error code if it exists.
 */

int check_file(char *full_path)
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
	/*if not exist the file*/
	errno = 127;
	return (127);
}
