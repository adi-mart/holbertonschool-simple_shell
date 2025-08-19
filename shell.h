#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_ARGS 64
extern char **environ;


char *read_line(void);
void execute_command(char **args, char *prog_name, int count);
void execute_child_process(char *cmd_path, char **args, char *prog_name, int count);
void handle_execve_error(char *prog_name, int count, char *cmd);
void print_prompt(void);
char **parse_line(char *line);
char *find_command(char *cmd);
char *get_path_env(void);

#endif
