#include "monty.h"

int init_stack(stack_t **stack)
{
	stack_t *s;

	s = malloc(sizeof(stack_t));
	if (!s)
		return (EXIT_FAILURE); /* malloc_error */

	s->n = STACK;
	(*stack) = s;

	return (EXIT_SUCCESS);
}


void free_stack(stack_t **stack)
{
	stack_t *temp = *stack;

	while (*stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
}


int is_stack(stack_t **stack)
{
	if ((*stack)->n == 0)
		return (1);
	return (0);
}
