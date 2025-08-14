#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * main - Entry point for the shell
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf(PROMPT);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			break;
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (line[0] == '\0')
			continue;

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(0);
		}
		pid = fork();

		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;
			execve(line, argv, environ);
			fprintf(stderr, "hsh: 1: %s: not found\n", line);
			exit(127);
		}
		else if (pid > 0)
			wait(&status);
		else
			perror("fork");
	}
	free(line);
	return (0);
}
