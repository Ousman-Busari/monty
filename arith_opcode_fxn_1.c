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
		add_err_to_optoks(pchar_error(line_number,
					      "value out of range"));
		return;
	}

	printf("%c\n", temp->n);
}

/**
 * interpret_pstr - prints the string starting at the top of the stack,
 *                  followed by a new line
 * @stack: the stack of the data
 * @line_number: the line number of the file where the fucntion is called
 *
 * Return: Nothing
 */
void interpret_pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;
	int char_count = 0, i;
	char *str;

	if ((*stack)->next == NULL)
	{
		printf("\n");
		return;
	}

	temp = (*stack)->next;
	while (temp && temp->n > 0 && temp->n <= 127)
	{
		char_count++;
		temp = temp->next;
	}

	if  (char_count == 0)
	{
		printf("\n");
		return ;
	}

	str = malloc(sizeof(char) * (char_count + 1));
	if (!str)
	{
		malloc_error();
		return;
	}

	temp = (*stack)->next;
	for (i = 0; i < char_count; i++)
	{
		str[i] = temp->n;
		temp = temp->next;
	}
	str[i] = '\n';
	printf("%s", str);
	free(str);
	(void) line_number;
}

/**
 * interpret_rotl - rotates the stack to the top
 * @stack: pointer to the head node of the list
 * @line_number: the current working line of the monty bytecodes file
 *
 * Return: Nothing
 */
void interpret_rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *temp_end, *temp_top;

	if ((*stack)->next == NULL)
		return;

	temp_end = (*stack)->next;
	while (temp_end->next)
		temp_end = temp_end->next;

	temp_top = (*stack)->next;

	temp_end->next = temp_top;
	(*stack)->next = temp_top->next;
	temp_top->next->prev = *stack;
	temp_top->prev = temp_end;
	temp_top->next = NULL;

	(void) line_number;
}

/**
 * interpret_rotr - rotates the stack to the bottom
 * @stack: pointer to the head node of the list
 * @line_number: the current working line of the monty bytecodes file
 *
 * Return: Nothing
 */
void interpret_rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp_end, *temp_top;

	if ((*stack)->next == NULL)
		return;

	temp_end = (*stack)->next;
	while (temp_end->next)
		temp_end = temp_end->next;

	temp_top = (*stack)->next;

	(*stack)->next = temp_end;
	temp_end->next = temp_top;
	temp_top->prev = temp_end;
	temp_end->prev->next = NULL;
	temp_end->prev = NULL;

	(void) line_number;
}
