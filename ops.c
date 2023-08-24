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
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		errno = EXIT_FAILURE;
		return;
	}
	printf("%d\n", (*stack)->n);
}

/**
 * pop - remove the top element of the stack
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - if the stack if empty, an error message is printed and errno
 * is set to EXIT_FAILURE
 */
void pop(stack_t **stack, unsigned int line_number)
{
	char *err_msg;
	stack_t *top = *stack;

	if (*stack == NULL)
	{
		err_msg = "L%d: can't pop an empty stack\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}

	if (top->next != NULL)
		top->next->prev = NULL;

	*stack = top->next;
	free(top);
}

/**
 * push - push an int onto the stack
 * @stack: a double pointer to the top of the stack
 * @n: integer to be pushed
 */
void push(stack_t **stack, int n)
{
	stack_t *new;

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

/**
 * swap - swao the top two elements of the stack
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - if the stack has < 2 elements, an error message
 * is printed and errno is set to EXIT_FAILURE
 */
void swap(stack_t **stack, unsigned int line_number)
{
	char *err_msg;
	size_t len;
	int tmp;
	stack_t *top;

	len = stack_len(*stack);
	if (len < 2)
	{
		err_msg = "L%d: can't swap, stack too short\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}

	top = *stack;
	tmp = top->n;
	top->n = top->next->n;
	top->next->n = tmp;
}
