#include "shell.h"

/**
 * _setenv - Set Environment variable
 * @args: Arguments passed.
 * @head: pointer to head.
 * Return: 0 on success, -1 on failure.
 */
int _setenv(char **args, char __attribute__((__unused__)) **head)
{
	const char *name;
	char *env_entry;
	const char *value;
	char **new_env;
	int i, j, n_l;

	name = args[0];
	value = args[1];
	if (args == NULL || args[0] == NULL || args[1] == NULL)
		return (-1);
	if (_strchr(name, '=') != NULL)
		return (-1);
	env_entry = (char *)malloc(_strlen(name) + _strlen(value) + 2);
	if (env_entry == NULL)
		return (-1);
	snprintf(env_entry, _strlen(name) + _strlen(value) + 2, "%s=%s", name, value);
	n_l = _strlen(name);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, n_l) == 0 && environ[i][n_l] == '=')
		{
			free(environ[i]);
			environ[i] = env_entry;
			return (0);
		}
	}
	new_env = (char **)malloc((i + 2) * sizeof(char *));
	if (new_env == NULL)
	{
		free(env_entry);
		return (-1);
	}
	for (j = 0; j < i; j++)
		new_env[j] = environ[j];
	new_env[i] = env_entry;
	new_env[i + 1] = NULL;
	environ = new_env;
	return (0);
}

/**
 * _unsetenv - UnsetSet Environment variable
 * @args: Arguments passed.
 * @front: pointer to head of argumets.
 * Return: 0 on success, -1 on failure.
 */
int _unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	const char *variable = args[0];
	int i, j, v_l;

	if (args == NULL || args[0] == NULL)
		return (-1);
	v_l = _strlen(variable);
	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], variable, v_l) == 0 && environ[i][v_l] == '=')
		{
			free(environ[i]);
			for (j = i; environ[j]; j++)
			{
				environ[j] = environ[j + 1];
			}
			return (0);
		}
	}
	return (0);
}

/**
 * _getenv - Get variable form PATH
 * @variable: Name of variable.
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */

char **_getenv(const char *variable)
{
	int len;
	char **env_var;

	if (variable == NULL || *variable == '\0' || environ == NULL)
		return (NULL);
	len = _strlen(variable);
	for (env_var = environ; *env_var; env_var++)
	{
		if (_strncmp(variable, *env_var, len) == 0 && (*env_var)[len] == '=')
		{
			return (env_var);
		}
	}
	return (NULL);
}







