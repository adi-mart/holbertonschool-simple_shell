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

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * parse_line - Splits the line into tokens (arguments)
 * @line: The command line to parse
 * Return: An array of pointers to the arguments (to be freed after use)
 */
char **parse_line(char *line)
{
	char *token, *line_copy;
	char **args = NULL;
	size_t bufsize = 64, i = 0;

	if (!line)
		return (NULL);

	args = malloc(bufsize * sizeof(char *));
	if (!args)
		return (NULL);

	line_copy = strdup(line);
	if (!line_copy)
	{
		free(args);
		return (NULL);
	}

	token = strtok(line_copy, " \t\n");
	while (token && i < bufsize - 1)
	{
		args[i++] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	free(line_copy);
	return (args);
}
