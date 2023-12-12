#include "shell.h"

/**
 * main - Simple shell program by Nkiru and Ayodeji.
 *
 * This program reads user commands and executes them.
 * @argc: command line arguments.
 * @argv: array of strings containing argc.
 * Return: Always 0.
 */

int main(int argc, char *argv[]);
int main(int argc, char *argv[])
{
	int i = 0;
	char *command = NULL;
	size_t buffsize = 1024;
	ssize_t bytereturned;
	char *token = NULL;
	int interactive = 1;
	char **args;

	(void)argc;
	(void)argv;

	while (1)
	{
		interactive = isatty(STDIN_FILENO);

		args = (char **)malloc(10 * sizeof(char *));
		if (args == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		if (interactive != 0)
		{
			int written = write(STDOUT_FILENO, "$ ", 2);

			if (written == -1)
			{
				perror("Error writing prompt");
				freemem(args);
				exit(EXIT_FAILURE);
			}
		}
		i = 0;
		bytereturned = getline(&command, &buffsize, stdin);

		if (bytereturned == -1)
		{
			perror("Error reading input");
			freemem(args);
			free(command);
			exit(EXIT_FAILURE);
		}
		if (interactive == 0)
			break;

		token = strtok(command, "\n\t\r");
		while (token != NULL)
		{
			args[i] = strdup(token);
			if (args[i] == NULL)
			{
				perror("Memory allocation error");
				freemem(args);
				free(command);
				exit(EXIT_FAILURE);
			}
			i++;
			token = strtok(NULL, "\n\t\r");
		}

		if (i == 0)
		{
			freemem(args);
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			freemem(args);
			free(command);
			exit_shell();
			break;
		}

		if (interactive == 0)
		{
			env();
		}
		execute_command(args[0]);
		freemem(args);
	}
	free(command);
	return (0);
}
