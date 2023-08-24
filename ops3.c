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
