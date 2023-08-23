#include "main.h"
#include <stdlib.h>

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
