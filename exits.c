#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the pointer to the destination string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (dest);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the pointer to the destination string
 */
char *_strncat(char *dest, char *src, int n)
{
	int dest_len = 0;
	int i;


	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}


	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}

	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: a pointer to the first occurrence of character c in s
 *         or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return ((char *)s);
	} while (*s++ != '\0');

	return (NULL);
}
