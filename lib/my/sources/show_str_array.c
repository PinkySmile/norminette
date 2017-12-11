/*
** EPITECH PROJECT, 2017
** show_str_array
** File description:
** Prints an array of strings
*/

#include "my.h"

void	show_str_array(char **tab)
{
	for (int i = 0; tab[i] != 0; i++) {
		my_put_nbr(i);
		my_putstr(":   ");
		my_putstr(tab[i]);
		my_putchar('\n');
	}
}
