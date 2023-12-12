#include "shell.h"

/**
 * validate_command - Validate user input for potentially dangerous characters.
 *  @command: The command to be validated.
 *
 *  This function checks if the command contains characters ';' or '&'.
 *
 *   Return: 1 if the command is invalid, 0 if it's valid.
 */

int validate_command(char *command)
{
if (strchr(command, ';') || strchr(command, '&'))
{
return (1);
}
return (0);
}
