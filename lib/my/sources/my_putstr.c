/*
** EPITECH PROJECT, 2017
** my_putstr
** File description:
** display a string
*/

#include "my.h"

int	my_putstr(char const *str)
{
	int	chars = 0;

	for (int i = 0; str[i] != '\0'; i++)
		chars += my_putchar(str[i]);
	return (chars);
}
