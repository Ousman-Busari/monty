#include "monty.h"

char **op_toks;
stack_t *stack;
unsigned int line_number = 0;

int is_empty_line(char *line, char *delims)
{
	int line_index, delims_index;

	for (line_index = 0; line[line_index]; line_index++)
	{
			for (delims_index = 0; delims[delims_index];
			     delims_index)
			{
				if (line[line_index] == delims[delims_index])
					break;
			}
			if (delims[delims_index] == '\0')
				return (0);
	}

	return (1);
}

unsigned int token_arr_len(void)
{
	unsigned int toks_len = 0;

	while (op_toks[toks_len])
		toks_len++;
	return (toks_len);
}

void (*get_interpreter(char *opcode))(stack_t **stack, unsigned int line_num)
{
	int i;
	instruction_t op_fxn[] = {
		{"push", interpret_push},
		{"pop", interpret_pop},
		{"pall", interpret_pall},
		{NULL, NULL}
	};

	for (i = 0; op_fxn[i].opcode; i++)
	{
		if (strcmp(opcode, op_fxn[i].opcode) == 0)
			return (op_fxn[i].f);
	}

	return NULL;
}

int monty_run(FILE *stream)
{
	void (*op_func)(stack_t **, unsigned int);
	char *line = NULL;
	unsigned int prev_tok_len = 0, i = 0;
	size_t len = 0, exit_status = EXIT_SUCCESS;

	while (getline(&line, &len, stream) != -1)
	{
		line_number++;
		op_toks = _strtok(line, DELIMS);
		if (op_toks == NULL)
		{
			if(is_empty_line(line, DELIMS))
				continue;
			return (98); /* memery allocation error */
		}

		if (op_toks[0][0] == '#')
		{
			free(op_toks);
			continue;
		}

		op_func = get_interpreter(op_toks[0]);
		if (op_func == NULL)
		{
			/* exit status = unknow_op_error(opo_toks[0], line_number) */
			free(op_toks);
			break;
		}
		prev_tok_len = token_arr_len();
		op_func(&stack, line_number);
		if (token_arr_len() != prev_tok_len)
		{
			if (op_toks && op_toks[prev_tok_len])
				exit_status = atoi(op_toks[prev_tok_len]);
			else
				exit_status = EXIT_FAILURE;
			free(op_toks);
			break;
		}
		free(op_toks);
	}

	if (line && *line == 0)
	{
		free(line);
		return (98);
	}

	free(line);
	return (exit_status);
}
