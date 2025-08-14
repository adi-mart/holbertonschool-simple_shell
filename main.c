#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * main - Entry point for the shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int status;

	while (1)
	{
<<<<<<< HEAD
		if (isatty(STDIN_FILENO))
			printf(PROMPT);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			break;
=======
		printf(PROMPT);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			exit(EXIT_FAILURE);
>>>>>>> pr2-corrected
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (line[0] == '\0')
			continue;
<<<<<<< HEAD

=======
>>>>>>> pr2-corrected
		pid_t pid = fork();

		if (pid == 0)
		{
			char *argv[2];

			argv[0] = line;
			argv[1] = NULL;

			execve(line, argv, environ);
			perror("./shell");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
			wait(&status);
		else
			perror("fork");
	}
	free(line);
	return (0);
}
