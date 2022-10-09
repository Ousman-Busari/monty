#define _GNU_SOURCE
#include "monty.h"
#include <stdio.h>

char **op_toks;

/**
 * add_err_to_optoks - converts error code to string
 *                     and add it to op_toks
 * @error_code: the error coode to be added
 *
 * Return: Nothing
 */
void add_err_to_optoks(int error_code)
{
	int tok_len = 0, i = 0;
	char *err_str = NULL;
	char **new_optoks = NULL;

	tok_len = token_arr_len();
	new_optoks = malloc(sizeof(char *) * (tok_len + 2));
	if (!new_optoks)
	{
		malloc_error();
		return;
	}

	while (i < tok_len)
	{
		new_optoks[i] = op_toks[i];
		i++;
	}

	err_str = malloc(sizeof(char) * 2);
	if (!err_str)
	{
		free(new_optoks);
		malloc_error();
		return;
	}

	err_str[0] = error_code + '0';

	new_optoks[i++] = err_str;
	new_optoks[i] = NULL;
	free(op_toks);
	op_toks = new_optoks;
}

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
		{"add", interpret_add},
		{"nop", interpret_nop},
		{"sub", interpret_sub},
		{"div", interpret_div},
		{"mul", interpret_mul},
		{"mod", interpret_mod},
		{"pchar", interpret_pchar},
		{"pstr", interpret_pstr},
		{"rotl", interpret_rotl},
		{"rotr", interpret_rotr},
		{"stack", interpret_stack},
		{"queue", interpret_queue},
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
		line_number++, op_toks = _strtok(line, DELIMS);
		if (op_toks == NULL)
		{
			free_stack(&stack);
			return (malloc_error());
		}
		if (!op_toks[0] || op_toks[0][0] == '#')
		{
			free_tokens();
			continue;
		}
		op_func = get_interpreter(op_toks[0]);
		if (op_func == NULL)
		{
			exit_status = unknown_opcode(op_toks[0], line_number);
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
	free_stack(&stack), free(line);
	return (exit_status);
}
