#include "shell.h"

/**
 * sig_handler - simple function handles ^C signal interupt
 * @uuv: Unused variable for signal function prototype
 *
 * Return: void
 */
static void sig_handler(int uuv)
{
	(void) uuv;
	if (sig_flag == 0)
		my_putstr("\n$ ");
	else
		my_putstr("\n");
}

/**
 * main - entry point for the custom shell program
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 on successful execution, or exit status
 * in case of errors.
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, a;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL, NULL};

	vars.argv = argv;
	vars.env = env_mode(environment);
	signal(SIGINT, sig_handler);
	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		my_putstr("$ ");
	sig_flag = 0;
	while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
	{
		sig_flag = 1;
		vars.count++;
		vars.commands = str_tokens(vars.buffer, ";");
		for (a = 0; vars.commands && vars.commands[a] != NULL; a++)
		{
			vars.av = str_tokens(vars.commands[a], "\n \t\r");
			if (vars.av && vars.av[0])
				if (builtins_check(&vars) == NULL)
					check_path_command(&vars);
		free(vars.av);
		}
		free(vars.buffer);
		free(vars.commands);
		sig_flag = 0;
		if (is_pipe == 0)
			my_putstr("$ ");
		vars.buffer = NULL;
	}
	if (is_pipe == 0)
		my_putstr("\n");
	rel_env_mode(vars.env);
	free(vars.buffer);
	exit(vars.status);
}
