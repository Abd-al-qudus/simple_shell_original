#include "main.h"

/**
* scan_env - set and search for the current path
*
* @environ: variable to check
*
* Return: linked list of env
*/

list_t *scan_env(char **environ)
{
	list_t *head;
	char *tok, *sev, *cp, *com, *envg, *path, *token;
	int i, j, k, true;

	com = "PATH", token = "=", path = ":";
	for (i = 0, j = 0, k = 0; environ[i] != NULL; i++)
	{
		sev = _strdup(environ[i]);
		cp = _strtok(sev, token);
		true = _strcmp(com, cp);
		if (true == 0)
		{
			j = i;
			break;
		}
		continue;
	}
	envg = environ[j];
	i = _strlen(envg), j = _strlen(com);
	while (k <= j)
	{
		int a;

		for (a = 0; a < i - 1; a++)
		{
			*(envg + a) = *(envg + a + 1);
		}
		*(envg + a) = '\0';
		k++;
	}
	tok = strtok(envg, path);
	head = NULL;
	while (tok != NULL)
	{
		add_node_end(&head, tok);
		tok = strtok(NULL, path);
	}
	return (head);
}

/**
* add_node_end - adds a new node at the end
* of a list_t list.
* @head: head of the linked list.
* @str: string to store in the list.
* Return: address of the head.
*/

list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new_h, *temp;

	new_h = malloc(sizeof(list_t));
	if (new_h == NULL)
		return (NULL);

	new_h->path = strdup(str);
	new_h->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_h;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_h;
	}

	return (*head);
}

/**
* scan_list - scan all the elements of a list_t list.
* @h: singly linked list.
* @buffer: buffer to check
* Return: scan result of elements in the list.
*/

char *scan_list(list_t *h, char *buffer)
{
	char *new_str, *path;

	path = NULL;
	new_str = NULL;
	while (h != NULL)
	{
		int resp;
		if (h->path == NULL)
			break;
		else
		{
			if (*(buffer + 0) == '/')
			{
				resp = access(buffer, F_OK);
				if (resp == 0)
				{
					new_str = buffer;
				}
			}
			else
			{
				path = _strdup(h->path);
				_strcat(path, "/");
				_strcat(path, buffer);
				resp = access(path, F_OK);
				if (resp == 0)
				{
					new_str = path;
				}
			}
		}
		h = h->next;
	}
	return (new_str);
}


/**
 * free_list - frees a list
 * @head: head of the linked list.
 * Return: no return.
 */

void free_path(list_t *head)
{
	list_t *current;

	while ((current = head) != NULL)
	{
		head = head->next;
		free(current->path);
		free(current);
	}
}

/**
* generate_env - return the environment
*
* @env: environment variable to get
* @environ: environ - environment
* return: a pointer to the environment
*/

char *generate_env(char **environ, char *env)
{
	char  *sev, *cp, *envg, *token;
	int i, j, k, true;

	token = "=";
	for (i = 0, j = 0, k = 0; environ[i] != NULL; i++)
	{
		sev = _strdup(environ[i]);
		cp = _strtok(sev, token);
		true = _strcmp(env, cp);
		if (true == 0)
		{
			j = i;
			break;
		}
		continue;
	}
	envg = environ[j];
	i = _strlen(envg), j = _strlen(env);
	while (k <= j)
	{
		int a;

		for (a = 0; a < i - 1; a++)
		{
			*(envg + a) = *(envg + a + 1);
		}
		*(envg + a) = '\0';
		k++;
	}
	return (envg);
}
