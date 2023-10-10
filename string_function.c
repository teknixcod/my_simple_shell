#include "shell.h"

/**
 * my_putstr - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t my_putstr(char *str)
{
	ssize_t number, lenght;

	number = str_len(str);
	lenght = write(STDOUT_FILENO, str, number);
	if (lenght != number)
	{
		perror("Error!");
		return (-1);
	}
	return (lenght);
}

/**
 * *str_dup - returns pointer to new mem alloc space which contains copy
 * @strdp: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *str_dup(char *strdp)
{
	char *copy;

		int lenght, i;

	if (strdp == 0)
		return (NULL);

	for (lenght = 0; strdp[lenght]; lenght++)
		;
	copy = malloc((lenght + 1) * sizeof(char));

	for (i = 0; i <= lenght; i++)
		copy[i] = strdp[i];

	return (copy);
}

/**
 * str_cmpr - compares two strings
 * @strcmp1: first string, of two, to be compared in length
 * @strcmp2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int str_cmpr(char *strcmp1, char *strcmp2)
{
	int k;

	k = 0;
	while (strcmp1[k] == strcmp2[k])
	{
		if (strcmp1[k] == '\0')
			return (0);
		k++;
	}
	return (strcmp1[k] - strcmp2[k]);
}

/**
 * *str_cat - concatenates two strings
 * @strct1: first string
 * @strct2: second string
 * Return: pointer
 */
char *str_cat(char *strct1, char *strct2)
{
	char *newstr;
	unsigned int lenght1, lenght2, newlen, i, j;

	lenght1 = 0;
	lenght2 = 0;
	if (strct1 == NULL)
		lenght1 = 0;
	else
	{
		for (lenght1 = 0; strct1[lenght1]; lenght1++)
			;
	}
	if (strct2 == NULL)
		lenght2 = 0;
	else
	{
		for (lenght2 = 0; strct2[lenght2]; lenght2++)
			;
	}
	newlen = lenght1 + lenght2 + 2;
	newstr = malloc(newlen * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	for (i = 0; i < lenght1; i++)
		newstr[i] = strct1[i];
	newstr[i] = '/';
	for (j = 0; j < lenght2; j++)
		newstr[i + 1 + j] = strct2[j];
	newstr[lenght1 + lenght2 + 1] = '\0';
	return (newstr);
}

/**
 * str_len - returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int str_len(char *str)
{
	unsigned int lenght;

	lenght = 0;

	for (lenght = 0; str[lenght]; lenght++)
		;
	return (lenght);
}
