#include "shell.h"

/**
 * env - Prints environmental variables.
 */
void env(void)
{
int i;

for (i = 0; environ[i] != NULL; i++)
{
if (write(1, environ[i], strlen(environ[i])) == -1)
{
perror("Error writing to stdout");
}
}
write(1, "\n", 1);
}
