/*
** EPITECH PROJECT, 2017
** my_strdup
** File description:
** Copy a string and return it
*/

#include "my.h"
#include <stdlib.h>

char	*my_strdup(char const *src)
{
	char *str;

	str = malloc((my_strlen(src) + 1) * sizeof(str));
	for (int i = 0; src[i] != 0; i++)
		str[i] = src[i];
	str[my_strlen(src)] = 0;
	return (str);
}
