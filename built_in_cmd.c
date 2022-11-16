#include "main.h"
#define MAX_BUILT_IN 5
#define MAX_PATH_SIZE 512

/**
* get_arg_list_length - get the length of argv
*
* @argv: list to conpute length
*
* Return: num of argument
*/

int get_arg_list_length(char **argv)
{
	int count;

	count = 0;
	for (count = 0; argv[count] != NULL; count++)
		;
	return (count);
}

/**
* _atoi - converts a string to an integer.
* @s: input string.
* Return: integer.
*/

int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;
		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}

/**
* eval_built_in - check whether a command is built in
*
* @cmd: command to check
* @arg: argument
*
* Return: 1 on success, -1 on failure
*/

int eval_built_in(char *cmd, char **argl, char **environ, list_t *env_var)
{
	char *built_in[MAX_BUILT_IN], *sh_path, path_name[MAX_PATH_SIZE];
	int res, check, i, argc, resp;
	size_t path_size;

	i = 0;
	res = -1;
	built_in[i] = "exit";
	built_in[i + 1] = "cd";
	built_in[i + 2] = "setenv";
	built_in[i + 3] = "unsetenv";
	built_in[i + 4] = "alias";
	path_size = MAX_PATH_SIZE;
	for (i = 0; i < MAX_BUILT_IN; i++)
	{
		check = _strcmp(cmd, built_in[i]);
		if (check == 0)
		{
			res = i;
			break;
		}
	}
	if (res == -1)
		return (-1);
	argc = get_arg_list_length(argl);
	switch (res)
	{
		case 0:
			if (!argl[1])
			{
				free(cmd);
				free_path(env_var);
				exit(0);
			}
			exit(_atoi(argl[1]));
			break;
		case 1:
			if (argc > 2)
			{
				perror("too many arguments");
				return (-1);
			}
			if (argl[1])
			{
				printf("agv is %s\n", argl[1]);
				if (_strcmp(argl[1], "-") == 0)
				{
					sh_path = generate_env(environ, "OLDPWD");
					chdir(sh_path);
					setenv("PWD", getcwd(path_name, path_size), 1);
					break;
				}
				else
				{
					chdir(argl[1]);
					setenv("PWD", getcwd(path_name, path_size), 1);
					break;
				}
			}
			else
			{
				sh_path = generate_env(environ, "HOME");
				chdir(sh_path);
			}
			break;
		case 2:
			resp = setenv(argl[1], argl[2], _atoi(argl[3]));
			if (resp == -1)
			{
				perror("failed");
				return (-1);
			}
			break;
		case 3:
			resp = unsetenv(argl[1]);
			if (resp == -1)
			{
				perror("unset ff");
				return (-1);
			}
			break;
		default:
			return (-1);
	}
	return (1);
}
