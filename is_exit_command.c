#include "shell.h"

/**
 * is_exit_command - Checks if the input command is "exit"
 * @line: The input command line*
 * Return: 1 if command is "exit", 0 otherwise
*/
int is_exit_command(char *line)
{
	return (strcmp(line, "exit") == 0);
}
