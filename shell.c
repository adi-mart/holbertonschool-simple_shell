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
 * execute_command - Forks and executes a command
 * @line: Command to execute
 * @prog_name: Name of the shell program
 * @count: Command count for error reporting
 *
 * Return: void
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
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, line);
		exit(127);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}

/**
 * main - Entry point for the simple shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;
	int command_count = 0;
	int i;
	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("($) ");
			fflush(stdout);
		}
		line = read_line();

		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
		{
			free(line);
			continue;
		}
		command_count++;
		execute_command(line + i, argv[0], command_count);
		free(line);
	}
	return (0);
}
