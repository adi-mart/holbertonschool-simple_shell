#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

extern char **environ;

#define PROMPT "$ "
#define UNUSED(x) (void)(x)

char **tokenize(char *line, const char *delim);
void free_tokens(char **toks);
char *resolve_path(const char *cmd);
int run_command(char **argv, const char *argv0, int cmdn);
int is_builtin(char **argv);
int bi_exit(char **argv);
int bi_env(void);

#endif
