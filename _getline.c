#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

/**
* _getline - read input from stdin
*
* @buffer: memory to store input
* @size: size of buffer to read
* @stream: file stream
*
* Return: numbers of byte read
*/

int _getline(char *buffer, size_t size, FILE *stream)
{
	int count;

	count = 0;
	if (stream != stdin)
		count = read(fileno(stream), buffer, size);
	count = read(STDIN_FILENO, buffer, size);
	if (count == -1)
		return (-1);
	return (count);
}
