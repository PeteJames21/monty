#include "monty.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/**
 * add - add the top two elements of the stack
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - The result is stored in the second top element
 * of the stack, and the top element is removed. If the stack has < 2 elements,
 * an error message is printed and errno is set to EXIT_FAILURE
 */
void add(stack_t **stack, unsigned int line_number)
{
	char *err_msg;
	size_t len;
	int sum;
	stack_t *top;

	len = stack_len(*stack);
	if (len < 2)
	{
		err_msg = "L%d: can't add, stack too short\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}

	top = *stack;
	sum = top->n + top->next->n;
	top->next->n = sum;
	pop(stack, line_number);
}
