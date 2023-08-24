#include "monty.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/**
 * pall - print all elements in the stack
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *h;
	(void)line_number;

	if (stack == NULL)
	{
		fprintf(stderr, "Error: invalid pointer to stack\n");
		errno = EXIT_FAILURE;
		return;
	}

	h = *stack;
	while (h)
	{
		printf("%d\n", h->n);
		h = h->next;
	}
}

/**
 * pint - print the int representation of the value at the top of the stack
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - if the stack is empty, an error message is printed and
 * errno is set to EXIT_FAILURE.
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL)
	{
		fprintf(stderr, "Error: invalid pointer to stack\n");
		errno = EXIT_FAILURE;
		return;
	}
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		errno = EXIT_FAILURE;
		return;
	}
	printf("%d\n", (*stack)->n);
}

/**
 * push - push an int onto the stack
 * @stack: a double pointer to the top of the stack
 * @n: integer to be pushed
 */
void push(stack_t **stack, int n)
{
	stack_t *new;

	if (stack == NULL)
	{
		fprintf(stderr, "Error: invalid pointer to stack\n");
		errno = EXIT_FAILURE;
		return;
	}

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		errno = EXIT_FAILURE;
		return;
	}

	new->n = n;
	new->prev = NULL;
	new->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = new;
	}

	*stack = new;
}
