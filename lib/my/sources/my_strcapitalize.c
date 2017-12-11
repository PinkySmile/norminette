/*
** EPITECH PROJECT, 2017
** my_strcapitalize
** File description:
** Capitalize the first letter of the words
*/

#include "my.h"

int	is_dig(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_up(char c)
{
	return (c >= 'A' && c <= 'Z');
}

int	is_low(char c)
{
	return (c >= 'a' && c <= 'z');
}

char	*my_strcapitalize(char *str)
{
	int	need_cap = 1;

	str = my_strlowcase(str);
	for (int i = 0 ; str[i] != '\0' ; i++) {
		if (is_dig(str[i]))
			need_cap = 0;
		if (is_low(str[i]) && need_cap == 1) {
			str[i] = str[i] - 'a' + 'A';
			need_cap = 0;
		}
		if (!is_low(str[i]) && !is_up(str[i]) && !is_dig(str[i]))
			need_cap = 1;
	}
	return (str);
}
