#include "monty.h"

/**
 * init_stack - initializes a linked list stack
 * @stack: pointer to the head pointer of the stack
 *
 * Return: Nothing
 */
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

/**
 * free_stack - frees a stack
 * @stack: address of the pointer to be freed
 *
 * Return
 */
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

/**
 * is_stack - determines if a linked list is a stack or not
 * @stack: address of the stack
 *
 * Return: Nothing
 */
int is_stack(stack_t **stack)
{
	if ((*stack)->n == 0)
		return (1);
	return (0);
}
