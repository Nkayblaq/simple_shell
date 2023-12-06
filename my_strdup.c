#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @str: The string to be duplicated.
 * Return: Pointer to the duplicated string.
 */

char *_strdup(char *str)
{
int size;
char *tmp;

if (str == NULL)
return (NULL);

size = strlen(str);
tmp = malloc(sizeof(char) * (size + 1));

if (tmp == NULL)
return (NULL);

strcpy(tmp, str);
return (tmp);
}
