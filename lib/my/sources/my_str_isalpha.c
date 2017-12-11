/*
** EPITECH PROJECT, 2017
** my_str_isalpha
** File description:
** return 1 if only alphabetical chars are in the string
*/

#include "my.h"

int	my_str_isalpha(char const *str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (!is_low(str[i]) && !is_up(str[i]))
			return (0);
	return (1);
}
