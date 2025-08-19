#include "shell.h"

/**
 * parse_line - Découpe la ligne en tokens (arguments)
 * @line: La ligne de commande à parser
 * Return: Un tableau de pointeurs vers les arguments (à free après usage)
 */
char **parse_line(char *line)
{
	char *token, *line_copy;
	char **args = NULL;
	size_t bufsize = 8, i = 0;

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
	while (token)
	{
		args[i++] = strdup(token);
		if (i >= bufsize)
		{
			bufsize *= 2;
			args = realloc(args, bufsize * sizeof(char *));
			if (!args)
				break;
		}
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	free(line_copy);
	return (args);
}
