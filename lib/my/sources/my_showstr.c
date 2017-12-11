/*
** EPITECH PROJECT, 2017
** my_showstr
** File description:
** Shows a string and the unprintable chars
*/

#include "my.h"

int	display_missing_zeros(unsigned char c)
{
	int	chars_displayed = 0;

	if (c < 8)
		chars_displayed += my_putchar('0');
	if (c < 32)
		chars_displayed += my_putchar('0');
	return (chars_displayed);
}

int	my_showstr(char const *str)
{
	int chars_displayed = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] < 32 || str[i] > 176) {
			chars_displayed += my_putchar('\\');
			chars_displayed += display_missing_zeros(str[i]);
			chars_displayed += my_putnbr_base(str[i], "01234567");
		} else
			chars_displayed += my_putchar(str[i]);
	}
	return (chars_displayed);
}
