/*
** EPITECH PROJECT, 2017
** my_putchar
** File description:
** print a character
*/

#include <unistd.h>

int	my_putchar(char c)
{
	return (write(1, &c, 1));
}
