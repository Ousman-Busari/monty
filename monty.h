#ifndef __MONTY_H__
#define __MONTY_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* structure / data type of stack elements */

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;


/* structure of the instructions to be performed on stacks */

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


/* global variables and MACROS*/
#define DELIMS  " \n\t\a\b"
extern stack_t *stack;
extern unsigned int line_number;
extern char **op_toks;

/* opcode functions */
void interpret_push(stack_t **stack, unsigned int line_number);
void interpret_pop(stack_t **stack, unsigned int line_number);
void interpret_pall(stack_t **stack, unsigned int line_number);


/* tokenize each line of the file */
int token_len(char *str, char *delims);
int tokens_count(char *str, char *delims);
char **_strtok(char *syt, char *delims);

/* interpretation functions */
int is_empty_line(char *line, char *delims);
unsigned int token_arr_len(void);
void (*get_interpreter(char *opcode))(stack_t **stack, unsigned int line_number);
int monty_run(FILE *stream);

#endif /* __MONTY_H__ */
