#include "monty.h"

/**
 * interpret_add - adds the top two elements of the stack
 * @stack: the stack of the data
 * @line_number: the line number of the file where the fucntion is called
 *
 * Return: Nothing
 */
void interpret_add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *temp1;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		add_err_to_optoks(short_stack_error(line_number, "add"));
		return;
	}

	temp = (*stack)->next;
	temp1 = temp->next;
	temp1->n += temp->n;
	(*stack)->next = temp1;
	temp1->prev = (*stack);
	free(temp);
}

/**
 * interpret_nop - does nothing on the tack
 * @stack: the stack of the data
 * @line_number: the line number of the file where the fucntion is called
 *
 * Return: Nothing
 */
void interpret_nop(stack_t **stack, unsigned int line_number)
{
	(void) stack;
	(void) line_number;
}

/**
 * interpret_sub - subtract the top two elements of the stack
 * @stack: the stack of the data
 * @line_number: the line number of the file where the fucntion is called
 *
 * Return: Nothing
 */
void interpret_sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *temp1;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		add_err_to_optoks(short_stack_error(line_number, "sub"));
		return;
	}

	temp = (*stack)->next;
	temp1 = temp->next;
	temp1->n -= temp->n;
	(*stack)->next = temp1;
	temp1->prev = (*stack);
	free(temp);
}

/**
 * interpret_div -  divides the second top element of the stack
 *                  by the top element of the stack
 * @stack: the stack of the data
 * @line_number: the line number of the file where the fucntion is called
 *
 * Return: Nothing
 */
void interpret_div(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *temp1;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		add_err_to_optoks(short_stack_error(line_number, "div"));
		return;
	}

	temp = (*stack)->next;
	if (temp->n == 0)
	{
		add_err_to_optoks(zero_div_error(line_number));
		return;
	}
	temp1 = temp->next;
	temp1->n /= temp->n;
	(*stack)->next = temp1;
	temp1->prev = (*stack);
	free(temp);
}

/**
 * interpret_mul - multiplies the second top element of the stack with the top
 *                 element of the stack
 * @stack: the stack of the data
 * @line_number: the line number of the file where the fucntion is called
 *
 * Return: Nothing
 */
void interpret_mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *temp1;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		add_err_to_optoks(short_stack_error(line_number, "mul"));
		return;
	}

	temp = (*stack)->next;
	temp1 = temp->next;
	temp1->n *= temp->n;
	(*stack)->next = temp1;
	temp1->prev = (*stack);
	free(temp);
}
