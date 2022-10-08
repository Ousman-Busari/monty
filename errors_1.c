#include "monty.h"

int file_error(char *file)
{
	fprintf(stderr, "Error: Can't open file %s\n", file);
	return (EXIT_FAILURE);
}

int malloc_error(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	return (EXIT_FAILURE);
}

int pop_error(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
	return (EXIT_FAILURE);
}

int swap_error(unsigned line_number)
{
	fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
	return (EXIT_FAILURE);
}
