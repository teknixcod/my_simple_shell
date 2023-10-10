#include "shell.h"

/**
 * add_keys - create a new environment variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void add_keys(vars_t *vars)
{
	unsigned int i;
	char **environs;

	for (i = 0; vars->env[i] != NULL; i++)
		;
	environs = malloc(sizeof(char *) * (i + 2));
	if (environs == NULL)
	{
		std_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (i = 0; vars->env[i] != NULL; i++)
		environs[i] = vars->env[i];
	environs[i] = add_value(vars->av[1], vars->av[2]);
	if (environs[i] == NULL)
	{
		std_error(vars, NULL);
		free(vars->buffer);
		free(vars->commands);
		free(vars->av);
		rel_env_mode(vars->env);
		free(environs);
		exit(127);
	}
	environs[i + 1] = NULL;
	free(vars->env);
	vars->env = environs;
}

/**
 * env_func - finds an environment variable
 * @env: array of environment variables
 * @key: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **env_func(char **env, char *key)
{
	unsigned int i, j, lenght;

	lenght = str_len(key);
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < lenght; j++)
			if (key[j] != env[i][j])
				break;
		if (j == lenght && env[i][j] == '=')
			return (&env[i]);
	}
	return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int lenght1, lenght2, i, j;
	char *new;

	lenght1 = str_len(key);
	lenght2 = str_len(value);
	new = malloc(sizeof(char) * (lenght1 + lenght2 + 2));
	if (new == NULL)
		return (NULL);
	for (i = 0; key[i] != '\0'; i++)
		new[i] = key[i];
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';
	return (new);
}

/**
 * _atoi - converts a string into an integer
 * @str: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int i, digits;
	int num = 0, num_test;

	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		num += str[i] - '0';
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (i > digits)
		return (-1);
	return (num);
}
