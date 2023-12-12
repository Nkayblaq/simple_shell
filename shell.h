#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 256

extern char **environ;

int my_strcmp(char *s1, char *s2);
int my_strlen(char *s);
char my_strdup(char *str);
void env(void);
int exit_shell(void);
void freemem(char **args);
int execute_command(char *command);
int validate_command(char *command);

#endif
