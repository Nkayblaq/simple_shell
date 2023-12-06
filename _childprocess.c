#include "shell.h"

/**
 * _childprocess - Creates a child process and executes a command.
 *
 * Return: The exit status of the executed command.
 */

int _childprocess(void);
int _childprocess(void)
{
int status;
pid_t pid;
ssize_t bytesRead;
char command[MAX_COMMAND_LENGTH];
char prompt[] = "simple_shell> ";

char **cmd_args = malloc(sizeof(char *) * 2);

pid = fork();

if (pid == 0)
{
if (write(STDOUT_FILENO, prompt, sizeof(prompt) - 1) == -1)
{
perror("Error writing prompt");
exit(EXIT_FAILURE);
}
bytesRead = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);
if (bytesRead == -1)
{
perror("Error reading input");
exit(EXIT_FAILURE);
}
else if (bytesRead == MAX_COMMAND_LENGTH - 1)
{
write(STDOUT_FILENO, "Input exceeding buffer size\n", 27);
exit(EXIT_FAILURE);
}
command[bytesRead] = '\0';
strtok(command, "\n");
if (cmd_args == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
cmd_args[0] = command;
cmd_args[1] = NULL;

execve(command, cmd_args, environ);
perror("Command not found: ");
write(STDOUT_FILENO, command, strlen(command));
write(STDOUT_FILENO, "\n", 1);
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("Fork failed");
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);

if (WIFEXITED(status))
{
return (WEXITSTATUS(status));
}
}
return (-1);
}

/**
 * execute_command - Executes a command in a child process.
 * @command: The command to be executed.
 */
void execute_command(char *command)
{
char *full_path = NULL;
char **cmd_args = NULL;
char *path_token;
pid_t pid;
int status;
int i = 0;
int num_args = 0;
char *path = getenv("PATH");

while (path && full_path == NULL)
{
path_token = strtok(NULL, " ");
if (!path_token)
{
break;
}
full_path = malloc(strlen(path) + strlen(path_token) + 2);
strcpy(full_path, path);
strcat(full_path, "/");
strcat(full_path, path_token);
if (access(full_path, F_OK) == -1)
{
free(full_path);
full_path = NULL;
}
}
if (!full_path)
{
perror("Command not found:");
return;
}
path_token = strtok(command, " ");
while (path_token)
{
num_args++;
path_token = strtok(NULL, " ");
}
cmd_args = malloc((num_args + 1) * sizeof(char *));
if (!cmd_args)
{
perror("malloc");
free(full_path);
return;
}
cmd_args[i++] = full_path;
path_token = strtok(command, " ");
while (path_token)
{
cmd_args[i++] = path_token;
path_token = strtok(NULL, " ");
}
cmd_args[i] = NULL;
pid = fork();
if (pid == 0)
{
execve(full_path, cmd_args, environ);
perror("Error executing command:");
write(STDOUT_FILENO, command, strlen(command));
write(STDOUT_FILENO, "\n", 1);
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);
free(full_path);
free(cmd_args);
}
}
