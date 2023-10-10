#include "shell.h"
/**
 * my_path_exec - Execute a command specified by its full path.
 *
 * @command: Full path to the command to be executed
 * @vars: Pointer to struct containing variables
 *
 * Return: 0 on success, 1 on failure
 */
int my_path_exec(char *command, vars_t *vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			std_error(vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, vars->av, vars->env) == -1)
				std_error(vars, NULL);
		}
		else
		{
			wait(&vars->status);
			if (WIFEXITED(vars->status))
				vars->status = WEXITSTATUS(vars->status);
			else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
				vars->status = 130;
			return (0);
		}
		vars->status = 127;
		return (1);
	}
	else
	{
		std_error(vars, ": Permission denied\n");
		vars->status = 126;
	}
	return (0);
}

/**
 * find_my_path - finds the PATH variable in the environment variables array
 *
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL if not found
 */
char *find_my_path(char **env)
{
	char *my_path = "PATH=";
	unsigned int a, b;

	for (a = 0; env[a] != NULL; a++)
	{
		for (b = 0; b < 5; b++)
			if (my_path[b] != env[a][b])
				break;
		if (b == 5)
			break;
	}
	return (env[a]);

}

/**
 * check_path_command - checks if the command is in the PATH
 * @vars: variables
 *
 * Return: void
 */
void check_path_command(vars_t *vars)
{
	char *my_path, *my_path_cpy = NULL, *search = NULL;
	unsigned int x = 0, y = 0;
	char **my_path_tokens;
	struct stat buf;

	if (my_path_dir(vars->av[0]))
		y = cwd_exec(vars);
	else
	{
		my_path = find_my_path(vars->env);
		if (my_path != NULL)
		{
			my_path_cpy = str_dup(my_path + 5);
			my_path_tokens = str_tokens(my_path_cpy, ":");
			for (x = 0; my_path_tokens && my_path_tokens[x]; x++, free(search))
			{
				search = str_cat(my_path_tokens[x], vars->av[0]);
				if (stat(search, &buf) == 0)
				{
					y = my_path_exec(search, vars);
					free(search);
					break;
				}
			}
			free(my_path_cpy);
			if (my_path_tokens == NULL)
			{
				vars->status = 127;
				new_exit(vars);
			}
		}
		if (my_path == NULL || my_path_tokens[x] == NULL)
		{
			std_error(vars, ": not found\n");
			vars->status = 127;
		}
		free(my_path_tokens);
	}
	if (y == 1)
		new_exit(vars);
}

/**
 * cwd_exec - executes command in current working directory
 *
 * @vars: pointer to struct of variables containing
 * command and environment information
 *
 * Return: 0 on success, 1 on failure
 */
int cwd_exec(vars_t *vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(vars->av[0], &buf) == 0)
	{
		if (access(vars->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				std_error(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->av[0], vars->av, vars->env) == -1)
					std_error(vars, NULL);
			}
			else
			{
				wait(&vars->status);
				if (WIFEXITED(vars->status))
					vars->status = WEXITSTATUS(vars->status);
				else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
					vars->status = 130;
				return (0);
			}
			vars->status = 127;
			return (1);
		}
		else
		{
			std_error(vars, ": Permission denied\n");
			vars->status = 126;
		}
			return (0);
	}
	std_error(vars, ": not found\n");
	vars->status = 127;
	return (0);
}

/**
 * my_path_dir - checks if the input string contains a directory path
 *
 * @str: string to check
 *
 * Return: 1 on success, 0 on failure
 */
int my_path_dir(char *str)
{
	unsigned int a;

	for (a = 0; str[a]; a++)
	{
		if (str[a] == '/')
			return (1);
	}
	return (0);
}
