#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	char **env = info->env;

	while (*env)
	{
		_puts(*env);
		_putchar('\n');
		env++;
	}
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	char **env = info->env;
	size_t len = _strlen(name);

	while (*env)
	{
		if (_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	char *name = info->argv[1];
	char *value = info->argv[2];

	int ret = setenv(name, value, 1);

	if (ret != 0)
	{
		_eputs("Failed to set environment variable\n");
		return (1);
	}

	return (0);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (int i = 1; i < info->argc; i++)
	{
		char *name = info->argv[i];
		int ret = unsetenv(name);

		if (ret != 0)
		{
			_eputs("Failed to unset environment variable\n");
			return (1);
		}
	}

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	char **env = environ;
	list_t *node = NULL;

	while (*env)
	{
		add_node_end(&node, *env, 0);
		env++;
	}

	info->env = node;
	return (0);
}
