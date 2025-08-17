#include "shell.h"

/**
 * print_prompt - Displays the shell prompt
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("($) ");
		fflush(stdout);
	}
}

/**
 * read_line - Reads a line from stdin
 * Return: pointer to the read string, or NULL if EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;

	nread = getline(&line, &size, stdin);
	if (nread == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * execute_command - Executes a given command
 * @line: the command to execute
 * @prog_name: the name of the shell program
 */
void execute_command(char *line, char *prog_name)
{
	pid_t pid;
	int status;
	char *args[2];

	if (strlen(line) == 0)
		return;

	pid = fork();

	if (pid == 0)
	{
		args[0] = line;
		args[1] = NULL;

		execve(line, args, environ);
		fprintf(stderr, "%s: No such file or directory\n", prog_name);
		exit(127);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
	}
}

/**
 * main - Entry point of the simple shell
 * @argc: Number of arguments (unused)
 * @argv: Array of arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;
	int i;
	(void)argc;

	while (1)
	{
		print_prompt();
		line = read_line();

		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
		{
			free(line);
			continue;
		}

		execute_command(line + i, argv[0]);
		free(line);
	}

	return (0);
}
