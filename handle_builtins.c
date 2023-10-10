#include "shell.h"

/**
 * builtins_check - checks if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*builtins_check(vars_t *vars))(vars_t *vars)
{
	unsigned int k;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (k = 0; check[k].f != NULL; k++)
	{
		if (str_cmpr(vars->av[0], check[k].name) == 0)
			break;
	}
	if (check[k].f != NULL)
		check[k].f(vars);
	return (check[k].f);
}

/**
 * new_exit - exit program
 * @vars: variables
 * Return: void
 */
void new_exit(vars_t *vars)
{
	int status;

	if (str_cmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		status = _atoi(vars->av[1]);
		if (status == -1)
		{
			vars->status = 2;
			std_error(vars, ": Illegal number: ");
			printstdo(vars->av[1]);
			printstdo("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->status = status;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	rel_env_mode(vars->env);
	exit(vars->status);
}

/**
 * _env - prints the current environment
 * @vars: struct of variables
 * Return: void.
 */
void _env(vars_t *vars)
{
	unsigned int i;

	for (i = 0; vars->env[i]; i++)
	{
		my_putstr(vars->env[i]);
		my_putstr("\n");
	}
	vars->status = 0;
}

/**
 * new_setenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void new_setenv(vars_t *vars)
{
	char **key;
	char *var;

	if (vars->av[1] == NULL || vars->av[2] == NULL)
	{
		std_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = env_func(vars->env, vars->av[1]);
	if (key == NULL)
		add_keys(vars);
	else
	{
		var = add_value(vars->av[1], vars->av[2]);
		if (var == NULL)
		{
			std_error(vars, NULL);
			free(vars->buffer);
			free(vars->commands);
			free(vars->av);
			rel_env_mode(vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	vars->status = 0;
}

/**
 * new_unsetenv - remove an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenv(vars_t *vars)
{
	char **key, **newenv;

	unsigned int i, j;

	if (vars->av[1] == NULL)
	{
		std_error(vars, ": Incorrect number of arguments\n");
		vars->status = 2;
		return;
	}
	key = env_func(vars->env, vars->av[1]);
	if (key == NULL)
	{
		std_error(vars, ": No variable to unset");
		return;
	}
	for (i = 0; vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * i);
	if (newenv == NULL)
	{
		std_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (i = 0; vars->env[i] != *key; i++)
		newenv[i] = vars->env[i];
	for (j = i + 1; vars->env[j] != NULL; j++, i++)
		newenv[i] = vars->env[j];
	newenv[i] = NULL;
	free(*key);
	free(vars->env);
	vars->env = newenv;
	vars->status = 0;
}
