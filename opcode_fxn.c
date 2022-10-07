#include "monty.h"

/**
 * interpret_push - pushes an element a stack_t linked list
 * @stack: pointer to the head node of the list
 * @line_number: the current working line of the monty bytecodes file
 *
 * Return: Nothing
 */

void interpret_push(stack_t **stack, unsigned int line_number)
{
	stack_t *new_ele;
	int i = 0;

	new_ele = malloc(sizeof(stack_t));
	if (!new_ele)
		return;

	if (op_toks[1] == NULL)
	{
		/* error message */
		return;
	}

	if (atoi(op_toks[1]) == 0 && op_toks[1] != "0")
		return; 	/* error message */

	new_ele->n = atoi(op_toks[1]);
	new_ele->next = NULL;
	new_ele->prev = NULL;

	if (*stack == NULL)
		*stack = new_ele;
	else
	{
		new_ele->next = *stack;
		(*stack)->prev = new_ele;
		*stack = new_ele;
	}
}

void interpret_pop(stack_t **stack, unsigned line_number)
{
	stack_t *temp;

	if (*stack == NULL)
		return;

	temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}


void interpret_pall(stack_t **stack, unsigned line_number)
{
	stack_t *temp;

	temp = *stack;
	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}
