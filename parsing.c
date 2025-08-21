#include "shell.h"

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
