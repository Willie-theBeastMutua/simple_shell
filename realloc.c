#include "shell.h"
/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: pointer to string array
 */
void ffree(char **pp)
{
	char **ptr = pp;

	if (!pp)
		return;


	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(pp);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ed block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p = malloc(new_size);
	unsigned int min_size = old_size < new_size ? old_size : new_size;
	unsigned int i = 0;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);


	if (!p)
		return (NULL);


	for (i = 0; i < min_size; i++)
		p[i] = ((char *)ptr)[i];

	free(ptr);
	return (p);
}
