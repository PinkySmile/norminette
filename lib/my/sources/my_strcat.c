/*
** EPITECH PROJECT, 2017
** my_strcat.c
** File description:
** Concatenate 2 strings
*/

#include "my.h"

char	*my_strcat(char *dest, char const *src)
{
	int length = my_strlen(dest);
	int i = 0;

	for (; src[i] != 0; i++)
		dest[i + length] = src[i];
	dest[i] = 0;
	return (dest);
}
