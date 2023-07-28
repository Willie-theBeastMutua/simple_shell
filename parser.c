#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct (not used in this function)
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(__attribute__((unused)) info_t *info, char *path)
{
	struct stat st;

	return (path && !stat(path, &st) && (st.st_mode & S_IFREG));
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct (not used in this function)
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(__attribute__((unused)) info_t *info, char *pathstr, char *cmd)
{
	int i, curr_pos = 0;
	char *path;

	if (!pathstr || !cmd)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	for (i = 0; ; i++)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = malloc(i - curr_pos + _strlen(cmd) + 2);
			if (!path)
				return (NULL);

			_strncpy(path, pathstr + curr_pos, i - curr_pos);
			if (*path)
				_strcat(path, "/");
			_strcat(path, cmd);

			if (is_cmd(info, path))
				return (path);

			bfree((void **)&path);
			if (!pathstr[i])
				break;
			curr_pos = i + 1;
		}
	}

	return (NULL);
}
