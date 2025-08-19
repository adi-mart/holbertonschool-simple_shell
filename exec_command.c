#include "shell.h"

/**
 * handle_builtin_commands - Handle built-in commands like exit
 * @args: Array of command arguments
 * @status: Pointer to shell status (unused for exit)
 * Return: 1 if command was handled, 0 otherwise
 */
int handle_builtin_commands(char **args, int *status)
{
	(void)status;

	if (strcmp(args[0], "exit") == 0)
	{
		exit(0);
	}
	return (0);
}

/**
 * handle_execve_error - Handles execve errors and exits with appropriate code
 * @prog_name: the name of the shell program
 * @count: The command count for error messages
 * @cmd: The command that failed
 */
void handle_execve_error(char *prog_name, int count, char *cmd)
{
	if (errno == EACCES)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
			prog_name, count, cmd);
		exit(126);
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, cmd);
		exit(127);
	}
}

/**
 * execute_child_process - Executes command in child process
 * @cmd_path: Path to the command to execute
 * @args: Array of arguments
 * @prog_name: the name of the shell program
 * @count: The command count for error messages
 */
void execute_child_process(char *cmd_path, char **args,
	char *prog_name, int count)
{
	if (execve(cmd_path, args, environ) == -1)
		handle_execve_error(prog_name, count, args[0]);
}

/**
 * execute_command - Executes a given command with PATH resolution
 * @args: Array of arguments for the command to execute
 * @prog_name: the name of the shell program
 * @count: The command count for error messages
 * @status: pointer to the shell status
 */
void execute_command(char **args, char *prog_name, int count, int *status)
{
	pid_t pid;
	int child_status;
	char *cmd_path;

	if (!args || !args[0] || !prog_name)
		return;

	if (handle_builtin_commands(args, status))
		return;

	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, args[0]);
		*status = 127;
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return;
	}
	else if (pid == 0)
		execute_child_process(cmd_path, args, prog_name, count);
	else
	{
		if (waitpid(pid, &child_status, 0) == -1)
			perror("waitpid");
		else
			*status = WEXITSTATUS(child_status);
	}
	free(cmd_path);
}
