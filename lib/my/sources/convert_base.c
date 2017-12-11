/*
** EPITECH PROJECT, 2017
** convert_base
** File description:
** Converts and display a number to a given base
*/

#include "my.h"
#include <stdlib.h>

char	*create_str(int neg, unsigned int number, int base_size,	\
char const *base_to)
{
	char	*str;
	int	nb_of_chars = 0;
	char	all_chars[32];

	for (int i = 0; number > 0; i++) {
		all_chars[i] = base_to[number % base_size];
		nb_of_chars++;
		number = number / base_size;
	}
	if (neg == 1)
		str = malloc(nb_of_chars);
	else {
		str[0] = '-';
		neg = 0;
		str = malloc(nb_of_chars + 1);
	}
	for (int i = nb_of_chars - neg; i >= 0; i--)
		str[i] = all_chars[i];
	str[nb_of_chars] = 0;
	return (str);
}

char	*convert_base(char const *nbr, char const *base_from,	\
char const *base_to)
{
	int		base_size;
	unsigned int	number;
	char		*str;
	int		neg = 1;

	number = my_getnbr_base(nbr, base_from);
	base_size = my_strlen(base_to);
	if (number < 0) {
		number *= -1;
		neg = -1;
	} else if (number == 0) {
		str = malloc(2);
		str[0] = base_to[0];
		str[1] = 0;
		return (str);
	}
	return (create_str(neg, number, base_size, base_to));
}
