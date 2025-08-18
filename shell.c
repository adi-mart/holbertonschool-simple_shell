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
 * execute_command - Executes a given command
 * @line: the command to execute
 * @prog_name: the name of the shell program
 * @count: The command count for error messages
 */
void execute_command(char *line, char *prog_name, int count)
{
	pid_t pid;
	int status;
	char *args[2];

	if (!line || strlen(line) == 0)
		return;

	args[0] = line;
	args[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		execve(line, args, environ);
		if (errno == EACCES)
		{
			fprintf(stderr, "%s: %d: %s: Permission denied\n", prog_name, count, line);
			exit(126);
		}
		else if (strchr(line, '/') != NULL)
		{
			fprintf(stderr, "%s: %d: %s: No such file or directory\n",
				prog_name, count, line);
			exit(2);
		}
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, line);
			exit(127);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
	}
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
	int i;
	int command_count = 1;
	int len;
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

		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
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
		execute_command(line + i, argv[0], command_count);
		free(line);
	}

	return (0);
}
