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

/**
 * handle_execve_error - Handles execve errors and exits with appropriate code
 * @prog_name: the name of the shell program
 * @count: The command count for error messages
 * @cmd: The command that failed
 */
void handle_execve_error(char *prog_name, int count, char *cmd)
{
	if (errno == EACCES)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
			prog_name, count, cmd);
		exit(126);
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, cmd);
		exit(127);
	}
}

/**
 * handle_exit_command - Handle exit command cleanup
 * @args: Array of arguments
 * @line: Command line to free
 */
void handle_exit_command(char **args, char *line)
{
	free_args(args);
	free(line);
}
