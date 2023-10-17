#include "shell.h"

/**
 * search_builtin - Matches command with function
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*search_builtin(char *command))(char **args, char **head)
{
	int i;
	built_t My_BuiltInCommands[] = {
		{ "exit", my_exit },
		{ "env", print_environment },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ NULL, NULL }
	};

	for (i = 0; My_BuiltInCommands[i].name; i++)
	{
		if (_strcmp(My_BuiltInCommands[i].name, command) == 0)
			break;
	}
	return (My_BuiltInCommands[i].func);
}

/**
 * my_exit - Causes Function Termination.
 * @args: An array of arguments containing the exit value.
 * @head: A double pointer to the beginning of args.
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 */
int my_exit(char **args, char **head)
{
	int exit_code;

	if (args[1] == NULL)
	{
		return (-3);
	}
	else
	{
		exit_code = _atoi(args[1]);
		if (exit_code == 0 && args[1][0] != '0')
		{
			printf("%s\n", args[1]);
			return (2);
		}
		else
		{
			args -= 1;
			free_arguments(args, head);
			exit(exit_code);
		}
	}
}


/**
 * print_environment - Causes Function Termination.
 * @args: An array of arguments containing the exit value.
 * @head: A double pointer to the beginning of args.
 * Return: integer
 */
int print_environment(char **args, char __attribute__((__unused__)) **head)
{
	char **env = environ;

	if (!environ)
		return (-1);
	while (*env != NULL)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
	(void)args;
	return (0);
}

