#include "shell.h"

/**
 * bfree - this frees a pointer and NULLS address.
 * @ptr: the address of the pointer to free.
 *
 * Return: 1 if freed, if not 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
