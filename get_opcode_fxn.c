#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>

char **op_toks;

/**
 * free_tokens - free an array of tokens
 *
 * Return: Nothing
 */
void free_tokens(void)
{
	size_t i = 0;

	if (op_toks == NULL)
		return;

	for (i = 0; op_toks[i]; i++)
		free(op_toks[i]);

	free(op_toks);
}

/**
 * is_empty_line - determines if a line is empty
 * @line: the pointer to the buffer containing the line
 * @delims: pointer to the strings of delimeter characters
 *
 * Return: 1 if empty, otherwise
 */
int is_empty_line(char *line, char *delims)
{
	int line_index, delims_index;

	for (line_index = 0; line[line_index]; line_index++)
	{
		for (delims_index = 0; delims[delims_index];
		     delims_index++)
		{
			if (line[line_index] == delims[delims_index])
				break;
		}
		if (delims[delims_index] == '\0')
			return (0);
	}

	return (1);
}


/**
 * token_arr_len - determines the length of an arr of tokens
 *
 * Return: length of the token arr
 */
unsigned int token_arr_len(void)
{
	unsigned int toks_len = 0;

	while (op_toks[toks_len])
		toks_len++;
	return (toks_len);
}

/**
 * get_interpreter - gets the interpreter for each opcode
 * @opcode: the opcode to be interpreted
 *
 * Return: Nothing
 */
void (*get_interpreter(char *opcode))(stack_t **stack, unsigned int line_num)
{
	int i;
	instruction_t op_fxn[] = {
		{"push", interpret_push},
		{"pop", interpret_pop},
		{"pall", interpret_pall},
		{"pint", interpret_pint},
		{"swap", interpret_swap},
		{NULL, NULL}
	};

	for (i = 0; op_fxn[i].opcode; i++)
	{
		if (strcmp(opcode, op_fxn[i].opcode) == 0)
			return (op_fxn[i].f);
	}

	return (NULL);
}


/**
 * monty_run - runs the monty bytecode interpreter on a file
 * @stream: the file or stream of lines of bytecode
 *
 * Return: EXIT_SUCCESS -on success, otherwise
 *         EXIT_FIALURE
 */

int monty_run(FILE *stream)
{
	stack_t *stack = NULL;
	void (*op_func)(stack_t **, unsigned int);
	char *line = NULL;
	unsigned int line_number = 0, prev_tok_len = 0;
	size_t len = 0, exit_status = EXIT_SUCCESS;

	if (init_stack(&stack) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	while (getline(&line, &len, stream) != -1)
	{
		line_number++;
		op_toks = _strtok(line, DELIMS);
		if (op_toks == NULL)
		{
			free_stack(&stack);
			return (malloc_error());
		}
		if (op_toks[0] == NULL)
		{
			if (is_empty_line(line, DELIMS))
				continue;
		}

		if (op_toks[0][0] == '#')
		{
			free_tokens();
			continue;
		}

		op_func = get_interpreter(op_toks[0]);
		if (op_func == NULL)
		{
			exit_status = unknown_instruction(op_toks[0],
							  line_number);
			free_tokens();
			break;
		}
		prev_tok_len = token_arr_len();
		op_func(&stack, line_number);
		if (token_arr_len() != prev_tok_len)
		{
			exit_status = atoi(op_toks[prev_tok_len]);
			free_tokens();
			break;
		}
		free_tokens();
	}

	free_stack(&stack);

	if (line && *line == 0)
	{
		free(line);
		return (98);
	}

	free(line);
	return (exit_status);
}
