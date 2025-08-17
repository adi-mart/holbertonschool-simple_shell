#include "shell.h"

/**
 * print_prompt - Displays the shell prompt
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("#cisfun$ ");
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
 * @command: the command to execute
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	if (strlen(command) == 0)
		return (1);

	pid = fork();

	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;

		if (execve(command, argv, environ) == -1)
		{
			fprintf(stderr, "./shell: No such file or directory\n");
			exit(127);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
	}

	return (1);
}

/**
 * main - Entry point of the simple shell
 * Return: 0 on success
 */
int main(void)
{
	char *line;

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

	if (strlen(line) == 0 || strspn(line, " \t") == strlen(line))
	{
		free(line);
		continue;
	}

	execute_command(line);
	free(line);
	}

	return (0);
}
