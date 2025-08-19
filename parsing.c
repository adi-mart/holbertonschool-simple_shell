#include "shell.h"


/**
 * parse_line - Splits a line into arguments
 * @line: The input line
 * Return: Array of argument strings (must be freed by caller)
 */
char **parse_line(char *line)
{
	char **args = malloc(sizeof(char *) * MAX_ARGS);
	char *token;
	int idx = 0;

	if (!args)
		return (NULL);

	token = strtok(line, " \t");
	while (token && idx < MAX_ARGS - 1)
	{
		args[idx++] = strdup(token);
		token = strtok(NULL, " \t");
	}
	args[idx] = NULL;
	return (args);
}
