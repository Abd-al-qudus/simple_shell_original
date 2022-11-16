#include <unistd.h>

/**
* _putchar - write single char to stdout
*
* @c: char to write
*
* Return: char to stdout
*/

int _putchar(char c)
{
	return (write(1, &c, 1));
}
