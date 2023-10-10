#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: commands to execute
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
	char *lineNumberStr;
} vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

/*******Environment.c*********/
char **env_mode(char **env);
void rel_env_mode(char **env);

ssize_t my_putstr(char *str);
char *str_dup(char *strdp);
int str_cmpr(char *strcmp1, char *strcmp2);
char *str_cat(char *strct1, char *strct2);
unsigned int str_len(char *str);

char **str_tokens(char *buffer, char *delimiter);
char **mem_realloc(char **ptr, size_t *mem);

/*****Newstrtok.c*****/
char *my_strtok(char *str, const char *delim);

void (*builtins_check(vars_t *vars))(vars_t *vars);
void new_exit(vars_t *vars);
void _env(vars_t *vars);
void new_setenv(vars_t *vars);
void new_unsetenv(vars_t *vars);

void add_keys(vars_t *vars);
char **env_func(char **env, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);

/*****Path.c*****/
void check_path_command(vars_t *vars);
int my_path_exec(char *command, vars_t *vars);
char *find_my_path(char **env);
int cwd_exec(vars_t *vars);
int my_path_dir(char *str);

/*******Errors.c***********/
void std_error(vars_t *vars, char *msg);
void printstdo(char *str);
char *_uitoa(unsigned int count);

/* global variable for handling ^C */
unsigned int sig_flag;


#endif /* _SHELL_H_ */
