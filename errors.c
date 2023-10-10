#include "shell.h"

/**
 * std_error - prints standard error message.
 *
 * @vars: struct variables pointer
 * @msg: message output
 *
 * Return: void
 */
void std_error(vars_t *vars, char *msg)
{
	char *lineNumberStr;
	int lineNumber;

	printstdo(vars->argv[0]);
	printstdo(": ");
	lineNumber = atoi(vars->lineNumberStr);
	lineNumberStr = _uitoa(lineNumber);
	printstdo(lineNumberStr);
	free(lineNumberStr);
	printstdo(": ");
	printstdo(vars->av[0]);
	if (msg)
	{
		printstdo(msg);
	}
	else
		perror("");
}

/**
 * printstdo - string output to standard error
 * @str: string output
 *
 * Return: void
 */
void printstdo(char *str)
{
	ssize_t digit, len;

	digit = str_len(str);
	len = write(STDERR_FILENO, str, digit);
	if (len != digit)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - unsigned int conversion into a string
 *
 * @count: unsigned int converter
 *
 * Return: pointer to converted string
 */
char *_uitoa(unsigned int count)
{
	char *digistr;
	unsigned int init, nums;

	init = count;
	for (nums = 0; init != 0; nums++)
		init /= 10;
	digistr = malloc(sizeof(char) * (nums + 1));
	if (digistr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	digistr[nums] = '\0';
	for (--nums; count; --nums)
	{
		digistr[nums] = (count % 10) + '0';
		count /= 10;
	}
	return (digistr);
}
