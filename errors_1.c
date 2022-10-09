#include "monty.h"

/**
 * file_error - prints message to stderr when a file can't be accesed
 * @file: name of the file
 *
 * Return: Nothing
 */

int file_error(char *file)
{
	fprintf(stderr, "Error: Can't open file %s\n", file);
	return (EXIT_FAILURE);
}

/**
 * malloc_error - prints message to stderr when malloc fails
 *
 * Return: Nothing
 */

int malloc_error(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	return (EXIT_FAILURE);
}


/**
 * pop_error - prints message to stderr when pop is called on an empty stack
 * @line_number: line number of the file where the error is encountered
 *
 * Return: Nothing
 */
int pop_error(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
	return (EXIT_FAILURE);
}

/**
 * zero_div_error - prints message to stderr when 0th element of stach is zero
 * @line_number: line number of the file where the error is encountered
 *
 * Return: Nothing
 */
int zero_div_error(unsigned int line_number)
{
	fprintf(stderr, "L%u: division by zero\n", line_number);
	return (EXIT_FAILURE);
}

/**
 * pchar_error - prints message to stderr If the value is not in the ascii table
 * @line_number: line number of the file where the error is encountered
 *
 * Return: Nothing
 */
int pchar_error(unsigned int line_number, char *situation)
{
	fprintf(stderr, "L%u: can't pchar, %s\n", line_number, situation);
	return (EXIT_FAILURE);
}
