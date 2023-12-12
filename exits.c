#include "shell.h"

/**
 * *_strncpy - this copies a str
 * @dest: destination str to be copied to
 * @src: src string
 * @n: amount of characters to be copied
 * Return: concatenated str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_strncat - this concatenates two strings
 * @dest: first str
 * @src: second str
 * @n: amount of bytes to be used
 * Return: concatenated str
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s =  dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * *strchr - this locates a character in a str
 * @s: str to be parsed
 * @c: character to look for
 * Return: (s) pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
