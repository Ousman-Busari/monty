#include "monty.h"

/**
 * interpret_mod - computes the rest of the division of the second top
 *                 element of the stack by the top element of the stack
 * @stack: the stack of the data
 * @line_number: the line number of the file where the fucntion is called
 *
 * Return: Nothing
 */
void interpret_mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *temp1;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		add_err_to_optoks(short_stack_error(line_number, "mod"));
		return;
	}

	temp = (*stack)->next;
	if (temp->n == 0)
	{
		add_err_to_optoks(zero_div_error(line_number));
		return;
	}
	temp1 = temp->next;
	temp1->n %= temp->n;
	(*stack)->next = temp1;
	temp1->prev = (*stack);
	free(temp);
}

/**
 * interpret_pchar - prints the char at the top of the stack,
 *                   followed by a new line
 * @stack: the stack of the data
 * @line_number: the line number of the file where the fucntion is called
 *
 * Return: Nothing
 */
void interpret_pchar(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if ((*stack)->next == NULL)
	{
		add_err_to_optoks(pchar_error(line_number, "stack empty"));
		return;
	}

	temp = (*stack)->next;
	if (temp->n < 0 || temp->n > 127)
	{
		add_err_to_optoks(pchar_error(line_number, "value out of range"));
		return;
	}

	printf("%c\n", temp->n);
}
