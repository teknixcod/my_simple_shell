#include "shell.h"

/**
 * **mem_realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @mem: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */
char **mem_realloc(char **ptr, size_t *mem)
{
	char **status;
	size_t j;

	status = malloc(sizeof(char *) * ((*mem) + 10));
	if (status == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (j = 0; j < (*mem); j++)
	{
		status[j] = ptr[j];
	}
	*mem += 10;
	free(ptr);
	return (status);
}
