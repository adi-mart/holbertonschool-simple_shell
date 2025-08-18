#include "shell.h"
/**
 * execute_command - Executes a given command
 * @line: the command to execute
 * @prog_name: the name of the shell program
 * @count: The command count for error messages
 */
void execute_command(char *line, char *prog_name, int count)
{
	pid_t pid;
	int status;
	char *args[2];

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
		/* Processus enfant */
		execve(line, args, environ);
		/* Si on arrive ici, execve a échoué */
		if (errno == EACCES)
		{
			fprintf(stderr, "%s: %d: %s: Permission denied\n", prog_name, count, line);
			exit(126);
		}
		else if (strchr(line, '/') != NULL)
		{
			fprintf(stderr, "%s: %d: %s: No such file or directory\n",
				prog_name, count, line);
			exit(2);
		}
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, line);
			exit(127);
		}
	}
	else
	{
		/* Processus parent */
		if (wait(&status) == -1)
			perror("wait");
	}
}
