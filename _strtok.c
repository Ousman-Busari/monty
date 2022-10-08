#define _GNU_SOURCE
#include <string.h>
#include "monty.h"

/**
 * token_len - determines the length of a token/word in a string
 *             before encountering the first delim character
 * @str: input string of words/tokens
 * @delims: string of characters used as delimeters
 *
 * Return: len of the first word/token encountered
 */

int token_len(char *str, char *delims)
{
	int index = 0, len = 0;
	int i, delims_len = 0;

	while (*(delims + delims_len))
		delims_len++;

	while (*(str + index))
	{
		for (i = 0; i < delims_len; i++)
		{
			if (*(str + index) == *(delims + i))
				return (len);
		}
		len++;
		index++;
	}
	return (len);
}


/**
 * tokens_count -counts the number of words/tokens in a string
 * @str: input string of words/tokens
 * @delims: string of characters to be used as delimeters
 *
 * Return: number of words/tokens in the input string
 */

int tokens_count(char *str, char *delims)
{
	int index = 0, count = 0, len = 0;
	int i, delims_len = 0, in = 0;

	while (*(delims + delims_len))
		delims_len++;

	while (*(str + len))
		len++;

	while (index < len)
	{
		in = 0;
		for (i = 0; i < delims_len; i++)
		{
			if (*(str + index) == *(delims + i))
			{
				in = 1;
				break;
			}
		}

		index++;

		if (in)
			continue;
		else
		{
			count++;
			index += token_len((str + index), delims);
		}

	}
	return (count);
}


/**
 * _strtok - puts the words/tokens in a string inside an array
 * @str: the input string of words/tokens
 * @delims: strings of characters to be used a delimeters
 *
 * Return: pointer to the array of words/tokens
 */

char **_strtok(char *str, char *delims)
{
	char **str_toks_arr;
	int index = 0;
	int i, delims_len = 0, in;
	int nth_token = 0, toks_count, tok_len;

	toks_count = tokens_count(str, delims);
	str_toks_arr = malloc(sizeof(char *) * (toks_count + 1));
	if (!str_toks_arr)
		return (NULL);

	while (*(delims + delims_len))
		delims_len++;

	for (; nth_token < toks_count; nth_token++)
	{
		for (; *(str + index); index++)
		{
			in = 0;
			for (i = 0; i < delims_len; i++)
			{
				if (*(str + index) == *(delims + i))
				{
					in = 1;
					break;
				}
			}

			if (in)
				continue;
			break;
		}

		tok_len = token_len((str + index), delims);
		str_toks_arr[nth_token] = strndup((str + index), tok_len);
		index += tok_len;
	}
	str_toks_arr[nth_token] = NULL;
	return (str_toks_arr);
}
