#include "shell.h"

/**
 * **str_tokens - tokenizes a buffer with a delimiter
 * @buffer: buffer to tokenize
 * @delimiter: delimiter to tokenize
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **str_tokens(char *buffer, char *delimiter)
{
	char **tokens = NULL;
	size_t j = 0, array = 10;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) * array);
	if (tokens == NULL)
	{
		perror("Error!");
		return (NULL);
	}
	while ((tokens[j] = my_strtok(buffer, delimiter)) != NULL)
	{
		j++;
		if (j == array)
		{
			tokens = mem_realloc(tokens, &array);
			if (tokens == NULL)
			{
				perror("Error!");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
