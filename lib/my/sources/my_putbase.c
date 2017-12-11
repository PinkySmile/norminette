/*
** EPITECH PROJECT, 2017
** my_putbase
** File description:
** All function which displays in a specific base
*/

#include "my.h"

int	my_puthexa(int *nbr)
{
	return (my_putnbr_base(*nbr, "0123456789abcdef"));
}

int	my_puthexa_cap(int *nbr)
{
	return (my_putnbr_base(*nbr, "0123456789ABCDEF"));
}

int	my_putoctal(int *nbr)
{
	return (my_putnbr_base(*nbr, "01234567"));
}

int	my_putbinary(int *nbr)
{
	return (my_putnbr_base(*nbr, "01"));
}
