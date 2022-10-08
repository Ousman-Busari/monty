#include "monty.h"


/**
 * not_int - prints messaage to stderr when a non_integer
 *           value is used with push
 * @line_number: the line number of the file where the errror is encountered
 *
 * Return: EXIT_FAILURE
 */

int not_int(unsigned int line_number)
{
	fprintf(stderr, "L%u: usage: push integer\n", line_number);
	return (EXIT_FAILURE);
}


/**
 * empty_stack - prints messaage to stderr when an operation is
 *               performed on the stack
 * @line_number: the line number of the file where the errror is encountered
 *
 * Return: EXIT_FAILURE
 */

int empty_stack(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
	return (EXIT_FAILURE);
}


/**
 * unknown_instruction - prints messaage to stderr when an unknown operation is
 *                       performed on the stack
 * @opcode: the specified operation
 * @line_number: the line number of the file where the errror is encountered
 *
 * Return: EXIT_FAILURE
 */

int unknown_opcode(char *opcode, unsigned int line_number)
{
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
	return (EXIT_FAILURE);
}

/**
 * usage_error - prints messaage to stderr when less or more than one arguments
 *               is used with the prog
 *
 * Return: EXIT_FAILURE
 */

int usage_error(void)
{
	fprintf(stderr, "USAGE: monty file\n");
	return (EXIT_FAILURE);
}
