#include "shell.h"

/**
 * _strlen - Finds the length of a string.
 * @s: The string to be counted.
 * Return: Length of the string.
 */

int _strlen(char *s)
{
int count = 0;

while (*s != '\0')
{
count++;
s++;
}
return (count);
}
