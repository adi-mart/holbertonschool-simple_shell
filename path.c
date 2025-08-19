#include "shell.h"

/**
 * find_command - Searches for a command in the directories of PATH
 * @cmd: The name of the command to search for
 * Return: The full path of the command or NULL if not found
 */
char *find_command(char *cmd)
{
	char *path, *path_copy, *dir, *full_path;

	if (!cmd)
		return (NULL);

	if (strchr(cmd, '/'))
		return (strdup(cmd));

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
