/*
** EPITECH PROJECT, 2017
** show_int_array
** File description:
** Shows an array of ints
*/

#include "my.h"

void	show_int_array(int *tab, int size)
{
	for (int i = 0; i < size; i++) {
		my_put_nbr(i);
		my_putstr(":  ");
		my_put_nbr(tab[i]);
		my_putchar('\n');
	}
}
