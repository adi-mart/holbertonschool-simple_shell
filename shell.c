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

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * main - Entry point of the simple shell
 * @argc: Number of arguments (unused)
 * @argv: Array of arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line;
	/* Unused argument */
	(void)argc;

	while (1)
	{
		print_prompt();
		line = read_line();
		/* Handle EOF (Ctrl+D) */
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}
		/* Handle empty line */
		if (strlen(line) == 0)
		{
			free(line);
			continue;
		}
		/* Pass program name for error messages */
		execute_command(line, argv[0]);
		free(line);
	}
	return (0);
}
