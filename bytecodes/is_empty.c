#include "monty.h"
#include <string.h>

int is_empty_line(char *line, char *delims)
{
	int line_index, delims_index;

	for (line_index = 0; line[line_index]; line_index++)
	{
		for (delims_index = 0; delims[delims_index];
		     delims_index++)
		{
			if (line[line_index] == delims[delims_index])
				break;
		}
		if (delims[delims_index] == '\0')
			return (0);
	}

	return (1);
}