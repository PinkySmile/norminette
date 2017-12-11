/*
** EPITECH PROJECT, 2017
** my_getnbr_base
** File description:
** Convert a number from a given base in decimal
*/

#include "my.h"

int	find_begin(char const *str)
{
	int	begin;

	for (begin = 0; str[begin] == '+' || str[begin] == '-'; begin++);
	return (begin);
}

int	find_digit_base(char c, char const *base)
{
	for (int i = 0; base[i] != 0; i++)
		if (c == base[i])
			return (i);
	return (-1);
}

int	my_getnbr_base(char const *str, char const *base)
{
	int	nbr = 0;
	int	begin = find_begin(str);
	int	exp = 0;
	int	digit;
	int	size = my_strlen(base);
	int	end = my_strlen(str);

	for (int i = end; i >= begin; i--) {
		digit = find_digit_base(str[i], base);
		if (digit != -1) {
			nbr = nbr + digit * my_compute_power_rec(size, exp);
			exp++;
		}
	}
	return (nbr);
}
