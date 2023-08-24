#include "monty.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/**
 * _mod - get the remainder on dividing the second stack element by the top
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - The result is stored in the second top element
 * of the stack, and the top element is removed. If the stack has < 2 elements
 * or the top element is zero, an error message is printed and errno is set
 * to EXIT_FAILURE
 */
void _mod(stack_t **stack, unsigned int line_number)
{
	char *err_msg;
	size_t len;
	int rem;
	stack_t *top;

	len = stack_len(*stack);
	if (len < 2)
	{
		err_msg = "L%d: can't mod, stack too short\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}

	top = *stack;
	if (top->n == 0)
	{
		err_msg = "L%d: division by zero\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}
	rem = top->next->n % top->n;
	top->next->n = rem;
	pop(stack, line_number);
}

/**
 * pchar - print the char at the top of the stack, followed by a newline
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - an error message is printed if the stack is empty or if the
 * value is not in the ASCII table (0 <= n <= 127). errno is set to
 * EXIT_FAILURE if an error occurs.
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	char *err_msg;
	size_t len;
	int n;

	len = stack_len(*stack);
	if (len == 0)
	{
		err_msg = "L%d: can't pchar, stack empty\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}

	n = (*stack)->n;
	if (n < 0 || n > 127)
	{
		err_msg = "L%d: can't pchar, value out of range\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}

	printf("%c\n", n);
}

/**
 * pstr - print the string starting at the top of the stack
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - The integer stored in each element of the stack is treated
 * as the ascii value of the character to be printed. The string stops when
 * either the stack is over, the value of the element if 0, or the value
 * is not in the ASCII table. A newline is printed if the stack is empty.
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *h;
	(void)line_number;

	h = *stack;
	while (h)
	{
		if (h->n <= 0 || h->n > 127)
			break;
		printf("%c", h->n);
		h = h->next;
	}
	printf("\n");
}

/**
 * rotl - rotate the stack to the top
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - The top element of the stack becomes the last one, and
 * the second top element of the stack becomes the first one. The function
 * never fails.
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	int n_top;
	stack_t *node;

	(void)line_number;
	node = *stack;
	if (node != NULL)
		n_top = node->n;
	while (node)
	{
		if (node->next)
		{
			node->n = node->next->n;
			node->next->n = n_top;
			node = node->next;
		}
		else
			break;
	}
}

/**
 * rotr - rotate the stack to the bottom
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - The last element of the stack becomes the top element
 * of the stack
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	int n_bottom;
	stack_t *node;

	(void)line_number;
	node = *stack;
	if (node == NULL)
		return;
	/* Move to the bottom and get the last elment */
	while (node)
	{
		if (node->next == NULL)
		{
			n_bottom = node->n;
			break;
		}
		node = node->next;
	}

	/* Push n_bottom to the top by swapping successive elements */
	while (node)
	{
		if (node->prev)
		{
			node->n = node->prev->n;
			node->prev->n = n_bottom;
			node = node->prev;
		}
		else
			break;
	}
}
