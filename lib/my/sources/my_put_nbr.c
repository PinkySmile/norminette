/*
** EPITECH PROJECT, 2017
** my_put_nbr
** File description:
** prints a number given as argument
*/

#include "my.h"

int get_number_length(int nb)
{
	char	length = 0;

	do {
		nb = nb / 10;
		length++;
	} while (nb != 0);
	return (length);
}

int number_exponant_n(int nb, int n)
{
	int	result = 1;

	while (n > 0) {
		result = result * nb;
		n--;
	}
	return (result);
}

int spe_case(int nb)
{
	if (nb == -2147483648)
		return (1);
	return (0);
}

static int handle_negs(int *nb)
{
	if (*nb < 0) {
		(*nb) *= -1;
		return (my_putchar('-'));
	}
	return (0);
}

int my_put_nbr(int nb)
{
	int	length_of_the_number;
	int	current_digit;
	int	digit_pos;
	int	number_left;
	int	chars_displayed = 0;

	if (spe_case(nb))
		return (my_putstr("-2147483648"));
	chars_displayed += handle_negs(&nb);
	number_left = nb;
	length_of_the_number = get_number_length(nb);
	digit_pos = length_of_the_number - 1;
	while (digit_pos >= 0) {
		current_digit = number_left / number_exponant_n(10, digit_pos);
		chars_displayed += my_putchar(current_digit + 48);
		number_left -= current_digit * number_exponant_n(10, digit_pos);
		digit_pos--;
	}
	return (chars_displayed);
}
