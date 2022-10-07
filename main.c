#include "monty.h"

int main(void)
{
	char **arr;
	int i = 0;
	char *str = "   pop 45    ", *t = "1$";

	printf("%d - \n", atoi(t));
	arr = _strtok(str, DELIMS);
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		free(arr[i++]);
	}
	free(arr);
	return (0);
}
