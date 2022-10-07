#include "monty.h"

int main(int ac, char **av)
{
	FILE *stream_fd = NULL;
	int exit_code = EXIT_SUCCESS;

	if (ac != 2)
		return (98); /* (usage_error()); */
	stream_fd = fopen(av[1], "r");
	if (stream_fd == NULL)
		return (98); /* (f_open_error(av[1])); */
	exit_code = monty_run(stream_fd);
	fclose(stream_fd);
	return (0); /* (exit_code); */
}
