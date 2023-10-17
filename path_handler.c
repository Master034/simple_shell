#include "shell.h"

/**
 * add_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *add_path_dir(char *path)
{
	char *temp_path, *pwd;
    int i, len = 0, pwd_length;
    
    pwd = *(_getenv("PWD")) + 4;
    pwd_length = _strlen(pwd);
    
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += pwd_length + 1;
			else
				len++;
		}
		else
			len++;
	}
	temp_path = malloc(sizeof(char) * (len + 1));
	if (!temp_path)
		return (NULL);
	temp_path[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(temp_path, pwd);
				_strcat(temp_path, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(temp_path, ":");
				_strcat(temp_path, pwd);
			}
			else
				_strcat(temp_path, ":");
		}
		else
		{
			_strncat(temp_path, &path[i], 1);
		}
	}
	return (temp_path);
}

/**
 * get_command - gets a command in the PATH.
 * @command: The command to Get.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *get_command(char *command)
{
    char **path, *temp;
	linked_l *dirs, *head;
	struct stat st;
	int dir_len, command_len;
	
	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);
		
	dirs = get_dir(*path + 5);
	head = dirs;
	dir_len = _strlen(dirs->dir);
	command_len = _strlen(command) + 2;
	
	while (dirs)
	{
		temp = malloc(dir_len + command_len);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * get_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
linked_l *get_dir(char *path)
{
	int index;
	char **dir_list, *temp_copy;
	linked_l *head = NULL, *new_node, *last;

	temp_copy = add_path_dir(path);
	if (!temp_copy)
		return (NULL);
	dir_list = _strtok(temp_copy, ":");
	free(temp_copy);
	if (!dir_list)
		return (NULL);

	new_node = malloc(sizeof(linked_l));
    if (!new_node)
	    return (NULL);

	for (index = 0; dir_list[index]; index++)
	{
	    	new_node->dir = dir_list[index];
        	new_node->next = NULL;
        	if (head)
        	{
        		while (last->next != NULL)
        			last = last->next;
        		last->next = new_node;
        	}
        	else
        	{
		        head = new_node;
		        last = head;
        	}
	    
		if (new_node == NULL)
		{
			free_list(head);
			free(dir_list);
			return (NULL);
		}
	}

	free(dir_list);

	return (head);
}


