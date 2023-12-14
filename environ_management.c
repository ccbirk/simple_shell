#include "shell.h"

/**
 * env_get_key - gets the value of an environ var
 * @key: the environment var
 * @data: structure of the program data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, data_of_program *data)
{
	int m, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (m = 0; data->env[m]; m++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[m], key_length) &&
		 data->env[m][key_length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[m] + key_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * env_set_key - overwrites the value of the environment var
 * or create it if doesn't exist.
 * @key: name of the var to set
 * @value: the new value
 * @data: structure of the program data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if success.
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int c, key_length = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (c = 0; data->env[c]; c++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[c], key_length) &&
		 data->env[c][key_length] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->env[c]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[c] = str_concat(str_duplicate(key), "=");
	data->env[c] = str_concat(data->env[c], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[c + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - this removes a key from the environ.
 * @key: key to remove
 * @data: struct of the program data
 * Return: 1 if the key was removed, 0 if the key does not exist.
 */
int env_remove_key(char *key, data_of_program *data)
{
	int f, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (f = 0; data->env[f]; f++)
	{/* iterates through the environ and checks for coincidences */
		if (str_compare(key, data->env[f], key_length) &&
		 data->env[f][key_length] == '=')
		{/* if key already exists, remove them */
			free(data->env[f]);

			/* move the others keys one position down */
			f++;
			for (; data->env[f]; f++)
			{
				data->env[f - 1] = data->env[f];
			}
			/* put the NULL value at the new end of the list */
			data->env[f - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - this prints the current environ
 * @data: structure for the program data
 * Return: nothing
 */
void print_environ(data_of_program *data)
{
	int h;

	for (h = 0; data->env[h]; h++)
	{
		_print(data->env[h]);
		_print("\n");
	}
}
