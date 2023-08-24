#include "monty.h"
#define  _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

/**
 * main - the entry point of the monty interpreter
 * @argc: the number of commandline args passed to monty
 * @argv: an array commandline args passed to monty
 * Return: the exit status code of the program
 */
int main(int argc, char **argv)
{
	FILE *fp;
	size_t line_size = 0;
	ssize_t len = 0;
	char *opcode, *arg, *line = NULL;
	unsigned int line_no = 0;
	int errcode;
	stack_t *main_stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	while ((len = getline(&line, &line_size, fp)) != EOF)
	{
		line_no++;
		opcode = strtok(line, " \n\t");
		if (opcode == NULL || opcode[0] == '#')
			continue;  /* Skip comments and blank lines */
		else
		{
			arg = strtok(NULL, " \n");
			/* Handle comments of the type `opcode#comment` */
			remove_comment(opcode);
			errcode = exec(opcode, arg, line_no, &main_stack);
			/* Stop the execution if an error is encountered */
			if (errcode != EXIT_SUCCESS)
				break;
		}
	}
	free(line);
	free_stack(main_stack);
	fclose(fp);
	return (errcode);
}
