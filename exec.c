#include "monty.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/**
 * exec - execute an opcode
 * @opcode: string representation of opcode
 * @arg: argument to pass to the opcode
 * @line_no: line number at which the opcode is found in the bytecode file
 * @stack: double pointer to the top of the stack
 * Return: 0 on success or EXIT_FAILURE on failure
 */
int exec(char *opcode, char *arg, unsigned int line_no, stack_t **stack)
{
	char *err_msg;
	int arg_int;
	void (*op_func)(stack_t **stack, unsigned int line_no);

	if (stack == NULL)  /* Can't be NULL but can be a pointer to NULL */
	{
		fprintf(stderr, "Error: invalid pointer to stack (NULL)\n");
		errno = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}

	op_func = get_op_func(opcode);
	errno = 0;
	if (strcmp(opcode, "push") == 0)
	{
		if (arg == NULL || is_int(arg) == 0)
		{
			err_msg = "L%d: usage: push integer\n";
			fprintf(stderr, err_msg, line_no);
			return (EXIT_FAILURE);
		}
		arg_int = atoi(arg);
		push(stack, arg_int);
	}
	else if (op_func == NULL)
	{
		err_msg = "L%d: unknown instruction %s\n";
		fprintf(stderr, err_msg, line_no, opcode);
		errno = EXIT_FAILURE;
	}
	else
		op_func(stack, line_no);

	return (errno);  /* errno is set by the op_func on failure */
}

/**
 * get_op_func - get the function corresponding to the opcode
 * @opcode: a string representation of the opcode
 * Return: a pointer to the function that will execute the opcode
 */
void (*get_op_func(char *opcode)) (stack_t **stack, unsigned int line_number)
{
	unsigned int i = 0;

	instruction_t instructions[] = {
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{NULL, NULL}
	};

	while (instructions[i].opcode != NULL)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
			return (instructions[i].f);
		i++;
	}

	return (NULL);  /* opcode not found */
}
