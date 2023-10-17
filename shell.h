#ifndef SHELL_H
#define SHELL_H
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUF_FLUSH -1
#define END_FILE -2
#define EXIT -3
#define MAX_COMMAND_LENGTH 100

extern char **environ;

/**
 * struct linked_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct linked_l.
 */
typedef struct linked_s
{
	char *dir;
	struct linked_s *next;
} linked_l;

/**
 * struct built_c - A new struct type defining builtin commands.
 * @name: Name of the command.
 * @func: A function pointer.
 */
typedef struct built_c
{
	char *name;
	int (*func)(char **argv, char **front);
} built_t;


int process_args(int *execution_return);
char *get_input(char *input, int *exe_ret);
int execute_args(char **args, char **front, int *exe_ret);
int execute(char **args, char **front __attribute__((unused)));
void *_realloc(void *o_pointer, unsigned int o_size, unsigned int n_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
const char *_strchr(const char *str, char c);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strcmp(char *str1, char *str2);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
int _atoi(const char *str);

int _setenv(char **args, char __attribute__((__unused__)) **head);
int _unsetenv(char **args, char __attribute__((__unused__)) **front);
char **_getenv(const char *variable);

linked_l *get_dir(char *path);
char *get_command(char *command);
char *add_path_dir(char *path);

void free_list(linked_l *head);

int (*search_builtin(char *command))(char **args,char **head);
int my_exit(char **args, char **head);
int print_environment(char **args, char __attribute__((__unused__)) **head);

void free_arguments(char **args, char **head);

#endif
