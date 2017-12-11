/*
** EPITECH PROJECT, 2017
** my_putchar
** File description:
** print a character
*/

#include <unistd.h>

int	my_putchar_stderr(char c)
{
	return (write(2, &c, 1));
}
