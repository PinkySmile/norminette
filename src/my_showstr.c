/*
** EPITECH PROJECT, 2017
** my_showstr
** File description:
** Shows a string and the unprintable chars
*/

#include "my.h"
#include <string.h>
#include <stdio.h>

int	display_missing_zeros(unsigned char c)
{
	int	chars_displayed = 0;

	if (c < 8)
		chars_displayed += printf("00");
	else if (c < 32)
		chars_displayed += printf("0");
	return (chars_displayed);
}

int	my_showstr(char const *str)
{
	int chars_displayed = 0;
	char	*nbr = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] < 32) {
			chars_displayed += printf("\\");
			chars_displayed += display_missing_zeros(str[i]);
			nbr = my_putnbrbase(str[i], "01234567");
			chars_displayed += printf("%s", nbr);
		} else
			chars_displayed += printf("%c", str[i]);
	}
	return (chars_displayed);
}
