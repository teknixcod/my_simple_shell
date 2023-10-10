#include "shell.h"
/**
 * char_match - checks if a given character matches
 * any character in a string
 *
 * @c: character to check
 * @str: string to check against
 *
 * Return: 1 if match, 0 if not
 */
unsigned int char_match(char c, const char *str)
{
	unsigned int alpha;

	for (alpha = 0; str[alpha] != '\0'; alpha++)
	{
		if (c == str[alpha])
			return (1);
	}
	return (0);
}

/**
 * my_strtok - a custom strtok function
 * @str: string to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to the next token or NULL
 */
char *my_strtok(char *str, const char *delim)
{
	static char *token_init;
	static char *current_token;
	unsigned int a;

	if (str != NULL)
		current_token = str;
	token_init = current_token;
	if (token_init == NULL)
		return (NULL);
	for (a = 0; current_token[a] != '\0'; a++)
	{
		if (char_match(current_token[a], delim) == 0)
			break;
	}
	if (current_token[a] == '\0' || current_token[a] == '#')
	{
		current_token = NULL;
		return (NULL);
	}
	token_init = current_token + a;
	current_token = token_init;
	for (a = 0; current_token[a] != '\0'; a++)
	{
		if (char_match(current_token[a], delim) == 1)
			break;
	}
	if (current_token[a] == '\0')
		current_token = NULL;
	else
	{
		current_token[a] = '\0';
		current_token = current_token + a + 1;
		if (*current_token == '\0')
			current_token = NULL;
	}
	return (token_init);
}
