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

	if (getline(&line, &size, stdin) == -1)
	{
		free(line);
		exit(0);
	}
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	return (line);
}

/**
 * execute_command - Executes a command by creating a new process
 * @line: The command to execute
 *
 * This function uses fork and execve to run the command.
 */
void execute_command(char *line)
{
	pid_t pid = fork();
	char *args[2];
	int status;

	if (pid == 0)
	{
		args[0] = line;
		args[1] = NULL;
		execve(line, args, environ);
		fprintf(stderr, "hsh: 1: %s: not found\n", line);
		exit(127);
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");
}

/**
 * main - Entry point for the test program
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Main loop reads and executes user commands. Type "exit" to quit.
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;
	(void)argc;
	(void)argv;

	while (1)
	{
		printf(PROMPT);
		line = read_line();
		if (is_exit_command(line))
		{
			free(line);
			exit(0);
		}
		if (line[0] == '\0' || line[0] == ' ' || line[0] == '\t')
		{
			free(line);
			continue;
		}
		execute_command(line);
		free(line);
	}
	return (0);
}
