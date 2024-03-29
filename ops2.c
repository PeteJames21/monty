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

/**
 * nop - do nothing
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * sub - add the top stack element from the second top element
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - The result is stored in the second top element
 * of the stack, and the top element is removed. If the stack has < 2 elements,
 * an error message is printed and errno is set to EXIT_FAILURE
 */
void sub(stack_t **stack, unsigned int line_number)
{
	char *err_msg;
	size_t len;
	int diff;
	stack_t *top;

	len = stack_len(*stack);
	if (len < 2)
	{
		err_msg = "L%d: can't sub, stack too short\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}

	top = *stack;
	diff = top->next->n - top->n;
	top->next->n = diff;
	pop(stack, line_number);
}

/**
 * _div - divide the second stack element by the top element
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - The result is stored in the second top element
 * of the stack, and the top element is removed. If the stack has < 2 elements
 * or the top element is zero, an error message is printed and errno is set
 * to EXIT_FAILURE
 */
void _div(stack_t **stack, unsigned int line_number)
{
	char *err_msg;
	size_t len;
	int quotient;
	stack_t *top;

	len = stack_len(*stack);
	if (len < 2)
	{
		err_msg = "L%d: can't div, stack too short\n";
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
	quotient = top->next->n / top->n;
	top->next->n = quotient;
	pop(stack, line_number);
}

/**
 * _mul - multiply the second stack element by the top element
 * @stack: a double pointer to the top of the stack
 * @line_number: line number in which the opcode is found
 * Description - The result is stored in the second top element
 * of the stack, and the top element is removed. If the stack has < 2 elements
 * an error message is printed and errno is set to EXIT_FAILURE
 */
void _mul(stack_t **stack, unsigned int line_number)
{
	char *err_msg;
	size_t len;
	int product;
	stack_t *top;

	len = stack_len(*stack);
	if (len < 2)
	{
		err_msg = "L%d: can't mul, stack too short\n";
		fprintf(stderr, err_msg, line_number);
		errno = EXIT_FAILURE;
		return;
	}

	top = *stack;
	product = top->next->n * top->n;
	top->next->n = product;
	pop(stack, line_number);
}
