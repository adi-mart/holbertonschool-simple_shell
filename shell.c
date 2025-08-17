#include "shell.h"

/**
 * read_line - Reads a line from standard input
 *
 * Return: Pointer to the read line (must be freed by caller)
 */
char *read_line(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;

	nread = getline(&line, &size, stdin);
	if (nread == -1)
	{
		free(line);
		if (feof(stdin))
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	return (line);
}

/**
 * execute_command - Executes a command by creating a new process
 * @line: The command to execute
 * @prog_name: The name of the shell program
 * @count: The command count for error messages
 *
 * This function uses fork and execve to run the command.
 */
void execute_command(char *line, char *prog_name, int count)
{
	pid_t pid = fork();
	char *args[2];
	int status;

	if (pid == 0)
	{
		args[0] = line;
		args[1] = NULL;
		execve(line, args, environ);
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
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}

/**
 * main - Entry point for the shell program
 * @argc: Number of arguments (unused)
 * @argv: Array of arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;
	int command_count = 0;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");
		line = read_line();

		if (line[0] == '\0' || line[0] == ' ' || line[0] == '\t')
		{
			free(line);
			continue;
		}
		command_count++;
		execute_command(line, argv[0], command_count);
		free(line);
	}
	return (0);
}
