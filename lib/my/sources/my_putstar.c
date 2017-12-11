/*
** EPITECH PROJECT, 2017
** my_putstr
** File description:
** displays
*/

#include "my.h"

int	my_putstarfloat(double *nbr)
{
	return (my_putfloat(*nbr, 6));
}

int	my_putstarint(int *nbr)
{
	return (my_put_nbr(*nbr));
}

int	my_putstarchar(char *c)
{
	return (my_putchar(*c));
}

int	my_putpointer(void *ptr)
{
	int		chars_displayed = 0;

	chars_displayed += my_putstr("0x");
	chars_displayed += my_putnbr_base((long)ptr, "0123456789abcdef");
	return (chars_displayed);
}

int	my_putnbr_unsigned(unsigned int *nbr)
{
	return (my_put_nbr_unsigned(*nbr));
}
