#include "shell.h"

/**
 * execute_command - Executes a given command
 * @args: Array of arguments for the command to execute
 * @prog_name: the name of the shell program
 * @count: The command count for error messages
 */
void execute_command(char **args, char *prog_name, int count)
{
	pid_t pid;
	int status;

	if (!args || !args[0] || !prog_name)
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			if (errno == EACCES)
			{
				fprintf(stderr, "%s: %d: %s: Permission denied\n",
					prog_name, count, args[0]);
				exit(126);
			}
			else if (strchr(args[0], '/') != NULL)
			{
				fprintf(stderr, "%s: %d: %s: No such file or directory\n",
					prog_name, count, args[0]);
				exit(2);
			}
			else
			{
				fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, args[0]);
				exit(127);
			}
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
	}
}
