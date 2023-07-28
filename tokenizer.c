#include "shell.h"


/**
 * _isspace - checks if a character is a whitespace character
 * @c: the character to check
 *
 * Return: 1 if c is a whitespace character, 0 otherwise
 */
int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

/**
 * _isdelim - checks if a character is a delimiter
 * @c: the character to check
 * @d: the delimiter string
 *
 * Return: 1 if c is a delimiter, 0 otherwise
 */
int _isdelim(char c, const char *d)
{
	while (*d)
	{
		if (*d == c)
			return (1);
		d++;
	}
	return (0);
}

/**
 * _strtok - custom implementation of strtok function
 * @str: the string to tokenize
 * @delim: the delimiter string
 *
 * Return: pointer to the next token, or NULL if no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *last_str;
	char *token;
	int in_token = 0;

	if (str == NULL)
		str = last_str;

	while (*str)
	{
		if (!_isdelim(*str, delim))
		{
			if (!in_token)
			{
				token = str;
				in_token = 1;
			}
		}
		else
		{
			if (in_token)
			{
				*str = '\0';
				last_str = str + 1;
				return (token);
			}
		}

		str++;
	}

	if (in_token)
	{
		last_str = str;
		return (token);
	}

	return (NULL);
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int num_words = 0, i;
	char **tokens, *token;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (d == NULL || d[0] == '\0')
		d = " ";

	for (i = 0; str[i]; i++)
	{
		if (!_isdelim(str[i], d) && (_isdelim(str[i + 1], d) || !str[i + 1]))
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	tokens = malloc((num_words + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	token = _strtok(str, d);

	while (token)
	{
		tokens[i] = _strdup(token);
		if (!tokens[i])
		{
			while (i >= 0)
				free(tokens[i--]);
			free(tokens);
			return (NULL);
		}
		i++;
		token = _strtok(NULL, d);
	}
	tokens[i] = NULL;
	return (tokens);
}
