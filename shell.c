#include "shell.h"

/**
 * main - Entry point of the simple shell
 * @argc: Number of arguments (unused)
 * @argv: Array of arguments
 * Return: The exit status of the last command executed
 */
int main(int argc, char **argv)
{
	char *line, **args;
	int i, command_count = 1, len, j, status = 0;
	(void)argc;

	while (1)
	{
		print_prompt();
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}
		for (i = 0; line[i] == ' ' || line[i] == '\t'; i++)
			;
		if (line[i] == '\0')
		{
			free(line);
			continue;
		}
		len = strlen(line);
		while (len > i && (line[len - 1] == ' ' || line[len - 1] == '\t'))
		{
			line[len - 1] = '\0';
			len--;
		}
		args = parse_line(line + i);
		if (args && args[0])
			execute_command(args, argv[0], command_count, &status);
		if (args)
		{
			for (j = 0; args[j]; j++)
				free(args[j]);
			free(args);
		}
		command_count++;
		free(line);
	}
	return (status);
}