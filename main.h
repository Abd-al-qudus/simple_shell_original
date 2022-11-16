#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct list_s
{
    char *path;
    struct list_s *next;
} list_t;

char *generate_env(char **environ, char *env);
void remove_end_of_line(char *line);
void print_current_dir(char *dir);
int _strlen(char *arr);
int _putchar(char c);
char *scan_list(list_t *h,char *buffer);
int _getline(char *buffer, size_t size, FILE *stream);
char *_strtok(char *str, const char *delim);
char *_strdup(char *src);
list_t *add_node_end(list_t **head, const char *str);
list_t *scan_env(char **environ);
char *_strcat(char *str1, char *str2);
int _strcmp(char *src1, char *scr2);
int execute(char **environ, char *buffer, char **av);
void generate_argv(char *param, char **argv);
int eval_built_in(char *cmd, char **argl, char **environ, list_t *env_var);
int get_arg_list_length(char **argv);
int _atoi(char *s);
char *get_dir(void);
void free_path(list_t *head);

#endif
