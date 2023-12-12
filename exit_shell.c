#include "shell.h"

/**
 * exit_shell - a function to exit my simple shell successfully
 *
 * Return: 0 on success
 */

int exit_shell(void)
{
exit(EXIT_SUCCESS);
}

/**
 * env - Prints the current environment.
 */

void env(void)
{
char **env_ptr = environ;
while (*env_ptr != NULL)
{
write(STDOUT_FILENO, *env_ptr, strlen(*env_ptr));
write(STDOUT_FILENO, "\n", 1);
env_ptr++;
}
}
