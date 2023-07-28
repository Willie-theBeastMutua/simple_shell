#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exitcheck;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *dir, buffer[1024];
	int chdir_ret;

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=") ? _getenv(info, "PWD=") : "/";
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(getcwd(buffer, 1024));
			_putchar('\n');
			return (1);
		}
		_puts(dir);
		_putchar('\n');
	}
	else
		dir = info->argv[1];

	chdir_ret = chdir(dir);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(dir);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	(void)info; /* Avoid unused parameter warning */

	_puts("Help information:\n");
	_puts("- exit: Exit the shell\n");
	_puts("- cd [directory]: Change the current directory\n");
	_puts("- help: Display help information\n");

	return (0);
}
