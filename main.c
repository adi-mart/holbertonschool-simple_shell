#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"
#include <stdlib.h>
/**
 * main - reads a line from standard input
 * @ac: argument count
 * @av: argument vector
 * Return: Always 0
 */
int main(int ac, char **av)

{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
        if (isatty(STDIN_FILENO))
            printf(PROMPT);
		nread = getline(&line, &len, stdin);
		if (nread == -1) 
        {
			perror("getline");
			exit(EXIT_FAILURE);;
		}
        if (nread > 0 && line[nread - 1] == '\n')
        {
            line[nread - 1] = '\0';
            continue;
        }
        if (nread == '\0')
        {
            continue;
        }
        if (nread == 1 && line[0] == ' ')
        {
            return (!NULL);
            printf("./shell: No such file or directory");
            continue;
        }
        
	}
	free(line);
	return (0);
}
