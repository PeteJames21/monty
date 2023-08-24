#include "monty.h"
#include <stdlib.h>

/**
 * is_int - check if a string represents an integer
 * @s: string to be evaluated
 * Return: 1 if s represents an integer, else 0
 */
int is_int(char *s)
{
	unsigned int i = 0;

	if (s == NULL)
		return (0);

	if (s[0] == '-' && s[1] != '\0')
		i++;

	for (; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}

	return (1);
}
