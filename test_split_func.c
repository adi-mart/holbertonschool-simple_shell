#include "shell.h"

int is_exit_command(char *line)
{
	return (strcmp(line, "exit") == 0);
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