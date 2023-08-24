#include "monty.h"
#include <stdlib.h>
#include <stddef.h>

/**
 * free_stack - free all memory allocated for the stack
 * @top: pointer to the top of the stack
 */
void free_stack(stack_t *top)
{
	stack_t *current;

	current = top;
	while (current != NULL)
	{
		if (current->prev != NULL)
			free(current->prev);

		if (current->next == NULL)
		{
			free(current);
			break;
		}
		current = current->next;
	}
}

/**
 * stack_len - determine the length of the stack
 * @stack: pointer to the top of the stack
 * Return: the number of elements in the stack
 */
size_t stack_len(stack_t *stack)
{
	size_t i = 0;

	while (stack)
	{
		stack = stack->next;
		i++;
	}

	return (i);
}
