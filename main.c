#include "main.h"
#define MAX_ARGV_SIZE 20
#define MAX_BUFFER_SIZE 4096


/**
* main - call other function
*
* @environ: env variables
*
* Return: Always 0
*/

int main(int ac __attribute__((unused)), char **av  __attribute__((unused)), char **environ)
{
	char buffer[MAX_BUFFER_SIZE], *env;
	list_t *env_var;
	size_t buf_size;
	int check, flag;
	char *agv[MAX_ARGV_SIZE];

	buf_size = MAX_BUFFER_SIZE;
	env_var = scan_env(environ);
	while (1)
	{
		_putchar('$');
		flag = _getline(buffer, buf_size, stdin);
		if (flag == -1)
			exit(1);
		remove_end_of_line(buffer);
		generate_argv(buffer, agv);
		check = eval_built_in(buffer, agv, environ, env_var);
		if (check == -1)
		{
			env = scan_list(env_var, buffer);
			if (env == NULL)
			{
				printf("%s: No such command\n", agv[0]);
				free(env);
			}
			else
			{
				execute(environ, env, agv);
				free(env);
			}
		}
	}
	return (0);
}


/**
* execute - execute a process
*
* @environ: environment variables
* @buffer: memory
* @av: argument vector
*
* Return: 0 on success, errno is set
*/

int execute(char **environ, char *buffer, char **av)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
		exit(0);
	else if (child_pid == 0)
	{
		int run_cmd;

		run_cmd = execve(buffer, av, environ);
		if (run_cmd == -1)
			exit(1);
	}
	wait(NULL);
	return (0);
}


/**
* generate_argv - generate the argument vector
*
* @param: pointer to tokenize
* @argl: argument list
*
* Return: argv pointer
*/

void generate_argv(char *param, char **argl)
{
	int i;
	char *token;
	char *result;
	const char *delim;

	i = 0;
	token = param;
	delim = " ";
	result = strtok(token, delim);
	while (result != NULL)
	{
		argl[i] = result;
		i++;
		result = strtok(NULL, delim);
	}
	argl[i] = NULL;
}

/**
* get_dir - get the current dir
*
* Return: dir
*/

char *get_dir(void)
{
	char *cwd, path[512];

	cwd = getcwd(path, 512);
	return (cwd);
}
