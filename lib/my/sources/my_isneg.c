/*
** EPITECH PROJECT, 2017
** my_isneg
** File description:
** Print either N if the number is negative or P if it is positive or null
*/

#include "my.h"

int my_isneg(int n)
{
	if (n < 0)
		my_putchar('N');
	else
		my_putchar('P');
}
