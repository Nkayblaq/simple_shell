#include "shell.h"

/**
 * freemem - a function to free the memory allocated for args array
 * @args: array to be freed
 * Return: void
 */

void freemem(char **args)
{
int i;

for (i = 0; args[i] != NULL; i++)
{
free(args[i]);
}
free(args);
}
