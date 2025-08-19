#include "shell.h"

/**
 * free_args - Free the array of arguments
 * @args: Array of arguments to free
 */
void free_args(char **args)
{
	int j;

	if (args)
	{
		for (j = 0; args[j]; j++)
			free(args[j]);
		free(args);
	}
}

/**
 * handle_exit_command - Handle exit command cleanup
 * @args: Array of arguments
 * @line: Command line to free
 */
void handle_exit_command(char **args, char *line)
{
	free_args(args);
	free(line);
}

/**
 * main - Entry point of the simple shell
 * @argc: Number of arguments (unused)
 * @argv: Array of arguments
 * Return: The exit status of the last command executed
 */
int main(int argc, char **argv)
{
	char *line, **args;
	int i, command_count = 1, len, status = 0;
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
		for (i = 0; line[i] == ' ' || line[i] == '\t';)
			i++;
		if (line[i] == '\0')
		{
			free(line);
			continue;
		}
		len = strlen(line);
		for (; len > i && (line[len - 1] == ' ' || line[len - 1] == '\t'); len--)
			line[len - 1] = '\0';

		args = parse_line(line + i);
		if (args && args[0])
		{
			if (execute_command(args, argv[0], command_count, &status))
			{
				handle_exit_command(args, line);
				break;
			}
		}
		free_args(args);
		command_count++;
		free(line);
	}
	return (status);
}
