#include "shell.h"

/**
 * _strtok - this separate strs with delims
 * @line: the pointer to array  received in getline.
 * @delim: the character of str in parts.
 * Return: pointer to the generated token
*/
char *_strtok(char *line, char *delim)
{
	int w;
	static char *str;
	char *copystr;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (w = 0; delim[w] != '\0'; w++)
		{
			if (*str == delim[w])
			break;
		}
		if (delim[w] == '\0')
			break;
	}
	copystr = str;
	if (*copystr == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (w = 0; delim[w] != '\0'; w++)
		{
			if (*str == delim[w])
			{
				*str = '\0';
				str++;
				return (copystr);
			}
		}
	}
	return (copystr);
}
