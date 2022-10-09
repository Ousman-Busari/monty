#include "monty.h"
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char *t = "School";
	char **tok;

	tok =_strtok(t, DELIMS);
	if (tok[0] == NULL)
	{
       		printf("Empty line\n");
	}
	return (0);
}
