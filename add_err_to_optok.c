#include "monty.h"

void add_err_to_optoks(int error_code)
{
	int tok_len = 0, i = 0;
	char *err_str = NULL;
	char **new_optoks = NULL;

	tok_len = token_arr_len();
	new_optoks = malloc(sizeof(char *) * (tok_len + 2));
	if(!new_optoks)
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
	if(!err_str)
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
