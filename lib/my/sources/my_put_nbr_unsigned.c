/*
** EPITECH PROJECT, 2017
** my_put_nbr
** File description:
** prints a number given as argument
*/

#include "my.h"

int get_number_lengths(unsigned int nb)
{
	char	length = 0;

	do {
		nb = nb / 10;
		length++;
	} while (nb != 0);
	return (length);
}

unsigned int number_eponant_n(unsigned int nb, int n)
{
	unsigned int	result = 1;

	while (n > 0) {
		result = result * nb;
		n--;
	}
	return (result);
}

int my_put_nbr_unsigned(unsigned int nb)
{
	int		length_of_the_number;
	int		current_digit;
	int		digit_pos;
	unsigned int	number_left;
	int		chars_displayed = 0;

	number_left = nb;
	length_of_the_number = get_number_lengths(nb);
	digit_pos = length_of_the_number - 1;
	while (digit_pos > -1) {
		current_digit = number_left / number_eponant_n(10, digit_pos);
		chars_displayed += my_putchar(current_digit + 48);
		number_left -= current_digit * number_eponant_n(10, digit_pos);
		digit_pos--;
	}
	return (chars_displayed);
}
