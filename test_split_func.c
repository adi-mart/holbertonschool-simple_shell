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

int main(int argc, char **argv)
{
	char *line;
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
	}
	return (0);
}