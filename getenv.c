#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: The array of environment strings.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t **head = &(info->env);

	int deleted = 0;

	if (!info->env || !var)
		return (0);


	while (*head)
	{
		if (starts_with((*head)->str, var))
		{
			list_t *temp = *head;
			*head = (*head)->next;
			free(temp->str);
			free(temp);
			info->env_changed = 1;
			deleted = 1;
		}
		else
		{
			head = &((*head)->next);
		}
	}

	return (deleted);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = malloc(_strlen(var) + _strlen(value) + 2);
	list_t *node = info->env;

	if (!var || !value)
		return (0);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);


	while (node)
	{
		if (starts_with(node->str, var))
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
