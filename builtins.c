#include "shell.h"

/**
 * handle_env_command - Print all environment variables
 */
void handle_env_command(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * handle_builtin_commands - Handle built-in commands like exit and env
 * @args: Array of command arguments
 * @status: Pointer to shell status (unused for exit)
 * Return: 1 if exit command, 2 if env command, 0 otherwise
 */
int handle_builtin_commands(char **args, int *status)
{
	(void)status;

	if (strcmp(args[0], "exit") == 0)
	{
		return (1);
	}
	if (strcmp(args[0], "env") == 0)
	{
		handle_env_command();
		return (2);
	}
	return (0);
}
