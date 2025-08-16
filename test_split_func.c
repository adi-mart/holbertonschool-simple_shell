#include "shell.h"

int is_exit_command(char *line)
{
	return (strcmp(line, "exit") == 0);
}

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
 * Ajouter une fonction char **parse_line(char *line)
 */

int main(int argc, char **argv)
{
	char *line; // Changer *line par **args Task 3
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
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		execute_command(line);
		free(line);
	}
	return (0);
}
