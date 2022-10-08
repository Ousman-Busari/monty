#include "monty.h"

/**
 * main -rums monty interpreter on an argument file
 * @ac: number of arguments
 * @av: pointer to the arrat of arguments
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */
int main(int ac, char **av)
{
	FILE *stream_fd = NULL;
	int exit_code = EXIT_SUCCESS;

	if (ac != 2)
		return (usage_error());
	stream_fd = fopen(av[1], "r");
	if (stream_fd == NULL)
		return (file_error(av[1]));
	exit_code = monty_run(stream_fd);
	fclose(stream_fd);
	return (exit_code);
}
