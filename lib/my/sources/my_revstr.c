/*
** EPITECH PROJECT, 2017
** my_evil_str
** File description:
** reverse a string
*/

#include "my.h"

void	my_swaps(char *c1, char *c2)
{
	char	buffer;

	buffer = *c1;
	*c1 = *c2;
	*c2 = buffer;
}

char	*my_revstr(char *str)
{
	int	length = 0;

	length = my_strlen(str);
	for (int i = 0; i < (length / 2); i++) {
		my_swaps(&str[i], &str[length - i - 1]);
	}
	return (str);
}
