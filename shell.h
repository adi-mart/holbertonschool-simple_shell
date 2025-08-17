#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

extern char **environ;

/* Function prototypes */
char *read_line(void);
void execute_command(char *line, char *prog_name, int count);
int is_exit_command(char *line);

#endif
