/*
** EPITECH PROJECT, 2017
** disp
** File description:
** display spaces for the function my_showmem
*/

#include "my.h"

void	disp(int sizes, int buffer)
{
	for (; sizes < 16; sizes++) {
		my_putstr("  ");
		if (buffer) {
			buffer = 0;
			my_putchar(' ');
		} else
			buffer++;
	}
}
