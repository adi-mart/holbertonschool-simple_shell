#include "shell.h"
#include <string.h>

/**
 * execute_command - Executes a given command
 * @line: the command to execute
 * @prog_name: the name of the shell program
 */
void execute_command(char *line, char *prog_name)
{
	pid_t pid;
	int status;
	char *args[2]; /* Only command and NULL */

	if (!line || strlen(line) == 0)
		return;

	args[0] = line;
	args[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		execve(args[0], args, environ);
		/* If execve returns, it means an error occurred */
		if (errno == EACCES)
		{
			fprintf(stderr, "%s: %s: Permission denied\n", prog_name, args[0]);
			exit(126);
		}
		else /* Command not found or other error */
		{
			fprintf(stderr, "%s: %s: not found\n", prog_name, args[0]);
			exit(127);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
	}
}
