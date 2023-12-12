#include "shell.h"

/**
 * execute_command - Executes a command in a child process.
 * @command: The command to be executed.
 *
 * This function creates a child process to execute the specified command.
 * It searches for the command executable in the PATH environment variable
 * and parses the command to extract arguments for execution.
 *
 * Return: The exit status of the executed command.
 */

int execute_command(char *command);
int execute_command(char *command)
{
	char *path_token_copy;
	char *full_path = NULL;
	char **cmd_args = NULL;
	char *path_token;
	pid_t pid;
	int status;
	int i = 0;
	int num_args = 0;
	char *path = getenv("PATH");

	if (strcmp(command, "exit") == 0)
	{
		exit_shell();
		return (0);
	}
	if (validate_command(command))
	{
		write(STDERR_FILENO, "Invalid command\n", 16);
		return (-1);
	}
	while (path && full_path == NULL)
	{
		path_token = strtok_r(NULL, ":", &path);
		if (!path_token)
		{
			break;
		}
		full_path = malloc(strlen(path) + strlen(path_token) + 2);
		if (!full_path)
		{
			perror("malloc");
			free(cmd_args);
			return (-1);
		}
		strcpy(full_path, path);
		strcat(full_path, "/");
		strcat(full_path, path_token);
		if (access(full_path, F_OK) == 0)
		{
			break;
		}
		free(full_path);
		full_path = NULL;
	}
	if (!full_path)
	{
		perror("Command not found:");
		freemem(cmd_args);
		return (-1);
	}
	path_token_copy = strdup(command);

	if (!path_token_copy)
	{
		perror("strdup");
		free(full_path);
		return (-1);
	}
	path_token = strtok(path_token_copy, " ");
	while (path_token)
	{
		num_args++;
		path_token = strtok(NULL, " ");
	}
	free(path_token_copy);
	cmd_args = malloc((num_args + 1) * sizeof(char *));
	if (!cmd_args)
	{
		perror("malloc");
		free(full_path);
		return (-1);
	}
	i = 0;
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
		_exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Fork failed");
		free(full_path);
		free(cmd_args);
		return (-1);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(full_path);
		free(cmd_args);
		return (WEXITSTATUS(status));
	}
}
