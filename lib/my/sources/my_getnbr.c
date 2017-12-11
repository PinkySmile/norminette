/*
** EPITECH PROJECT, 2017
** my_getnbr
** File description:
** extract a number from a string
*/

#include "my.h"

int	perform_op(int nbr, int *leave, int add)
{
	if (nbr * 10 + add < nbr) {
		*leave = 1;
		return (0);
	}
	nbr *= 10;
	nbr += add;
	return (nbr);
}

int	modify_sign(int *sign, char c, int found_nbr)
{
	if (c == '-' && found_nbr == 0) {
		*sign = *sign * -1;
		return (0);
	} else if (found_nbr == 0 && c == '+')
		return (0);
	return (1);
}

int	my_getnbr(char const *str)
{
	unsigned int	number = 0;
	int		leave = 0;
	int		found_nbr = 0;
	int		sign = 1;
	int		i = 0;

	while (leave == 0) {
		if (str[i] >= '0' && str[i] <= '9') {
			number = perform_op(number, &leave, str[i] - '0');
			found_nbr = 1;
		} else
			leave = modify_sign(&sign, str[i], found_nbr);
		i++;
	}
	if (sign > 0 && number >= 2147483648)
		number = 0;
	return (number * sign);
}
