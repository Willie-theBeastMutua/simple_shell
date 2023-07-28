#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	list_t *env = info->env;

	while (env)
	{
		_puts(env->str);
		_putchar('\n');
		env = env->next;
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
	list_t *env = info->env;
	char *name_copy = _strdup(name);
	size_t len = _strlen(name_copy);

	while (env)
	{
		char *env_var = env->str;

		if (_strcmp(env_var, name_copy) == 0 && env_var[len] == '=')
			return (env_var + len + 1);
		env = env->next;
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
	char *name = info->argv[1];
	char *value = info->argv[2];
	int ret = setenv(name, value, 1);

	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}


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
	int i = 0;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i < info->argc; i++)
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
