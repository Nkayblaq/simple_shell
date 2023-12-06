#include "shell.h"

/**
 * _strncpy - Copies a string up to n characters.
 * @dest: Destination string.
 * @src: Source string.
 * @n: Number of characters to copy.
 * Return: Pointer to the destination string (dest).
 */

char _strncpy(char *dest, const char *src, size_t n)
{
size_t i;

for (i = 0; i < n && src[i] != '\0'; i++)
dest[i] = src[i];

while (i < n)
{
dest[i] = '\0';
i++;
}
return (*dest);
}

