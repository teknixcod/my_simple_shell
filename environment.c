#include "shell.h"

/**
 * env_mode - create a shell environment from the environment passed to main
 *
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 *
 */

char **env_mode(char **env)
{
	char **nc_env = NULL;
	size_t z;

	for (z = 0; env[z] != NULL; z++)
		;

	nc_env = malloc(sizeof(char *) * (z + 1));

	if (nc_env == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}

	for (z = 0; env[z] != NULL; z++)
		nc_env[z] = str_dup(env[z]);
	nc_env[z] = NULL;

	return (nc_env);

}

/**
 * rel_env_mode - free environment
 *
 * @env: shell's environment
 *
 * Return: void
 */

void rel_env_mode(char **env)
{
	unsigned int a;

	for (a = 0; env[a] != NULL; a++)

	free(env[a]);
	free(env);
}
