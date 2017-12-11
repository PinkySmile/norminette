/*
** EPITECH PROJECT, 2017
** my_putfloat
** File description:
** Displays a float with a given decimals number
*/

#include "my.h"

int	display_dec_part(int dec_part, int decimals)
{
	int     dec_length = 0;
	int	chars_displayed = 0;
	int	decimal;

	if (dec_part < 0)
		dec_part *= -1;
	decimal = dec_part;
	do {
		decimal /= 10;
		dec_length++;
	} while (decimal > 0);
	for (int i = decimals - dec_length; i > 0; i--)
		chars_displayed += my_putchar('0');
	chars_displayed += my_put_nbr(dec_part);
	return (chars_displayed);
}

int	my_putfloat(double nbr, int decimals)
{
	long	number;
	long 	exponant;
	int	chars_displayed = 0;
	int	neg = 1;

	exponant = my_compute_power_rec_long(10, decimals);
	if (nbr < 0)
		neg *= -1;
	number = (long)(exponant * nbr + 0.5 * neg);
	if (number == 0)
		neg = 1;
	if (number > -exponant && neg == -1)
		chars_displayed += my_putchar('-');
	chars_displayed += my_put_nbr((int)(number / exponant));
	chars_displayed += my_putchar('.');
	chars_displayed += display_dec_part(number % exponant, decimals);
	return (chars_displayed);
}
