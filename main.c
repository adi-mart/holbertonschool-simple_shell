#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * main - Entry point for the shell
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;
	pid_t pid;
	int status;
	char *args[2];
    (void)argc;

	while (1)
	{
		printf(PROMPT);

		nread = getline(&line, &size, stdin);
		if (nread == -1)
		{
			if (line)
				free(line);
			exit(0);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		
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
	return (0);
}
