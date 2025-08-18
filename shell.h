#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

extern char **environ;

char *read_line(void);
void execute_command(char *line, char *prog_name, int count);
int is_exit_command(char *line);

#endif
