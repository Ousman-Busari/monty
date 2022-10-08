#include "monty.h"

/**
 * interpret_push - pushes an element to a stack_t linked list
 * @stack: pointer to the head node of the list
 * @line_number: the current working line of the monty bytecodes file
 *
 * Return: Nothing
 */
void interpret_push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_ele, *temp;
	int i;

	new_ele = malloc(sizeof(stack_t));
	if (!new_ele)
	{
		add_err_to_optoks(malloc_error());
		return;
	}
	if (op_toks[1] == NULL)
	{
		add_err_to_optoks(not_int(line_number));
		return;
	}
	for (i = 0; op_toks[1][i]; i++)
	{
		if (op_toks[1][i] == '-' && i == 0)
			continue;
		if (op_toks[1][i] < '0' || op_toks[1][i] > '9')
		{
			add_err_to_optoks(not_int(line_number));
			return;
		}
	}
	new_ele->n = atoi(op_toks[1]);
	if (is_stack(stack))
	{
		new_ele->prev = *stack;
		if ((*stack)->next)
		{
			temp = (*stack)->next;
			new_ele->next = temp;
			temp->prev = new_ele;
		}
		(*stack)->next = new_ele;
	}
	else
	{
		temp = (*stack)->next;
		while (temp)
			temp = temp->next;
		temp->next = new_ele;
		new_ele->prev = temp;
	}
}

/**
 * interpret_pall - prints all elements in a stack_t linked list
 * @stack: pointer to the head node of the list
 * @line_number: the current working line of the monty bytecodes file
 *
 * Return: Nothing
 */
void interpret_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	temp = *stack;
	while (temp->next)
	{
		printf("%d\n", temp->next->n);
		temp = temp->next;
	}
	(void) line_number;
}

/**
 * interpret_pint - prints the last element in a stack_t linked list
 * @stack: pointer to the head node of the list
 * @line_number: the current working line of the monty bytecodes file
 *
 * Return: Nothing
 */
void interpret_pint(stack_t **stack, unsigned int line_number)
{
	if ((*stack)->next)
		printf("%d\n", (*stack)->next->n);
	else
		add_err_to_optoks(empty_stack(line_number));
}

/**
 * interpret_pop - pops out the last element in a stack_t linked list
 * @stack: pointer to the head node of the list
 * @line_number: the current working line of the monty bytecodes file
 *
 * Return: Nothing
 */
void interpret_pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if ((*stack)->next)
	{
		temp = (*stack)->next;
		(*stack)->next = temp->next;
		free(temp);
	}
	else
		add_err_to_optoks(pop_error(line_number));
}

/**
 * interpret_swap - swaps the last two elementa in a stack_t linked list
 * @stack: pointer to the head node of the list
 * @line_number: the current working line of the monty bytecodes file
 *
 * Return: Nothing
 */
void interpret_swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp, *temp1;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		add_err_to_optoks(short_stack_error(line_number, "swap"));
		return;
	}

	temp = (*stack)->next;
	temp1 = temp->next;

	temp->next = temp1->next;
	if (temp1->next)
		temp1->next->prev = temp;
	temp1->next = temp;
	temp1->prev = *stack;
	temp->prev = temp1;
	(*stack)->next = temp1;
}
