/*
** EPITECH PROJECT, 2017
** compare_strings.c
** File description:
** Compare to strings return 1 if same or 0
*/

#include <string.h>

int	compare_strings(char *str1, char *str2)
{
	if (strlen(str1) != strlen(str2))
		return (0);
	for (unsigned int i = 0; i < strlen(str1); i++)
		if (str1[i] != str2[i])
			return (0);
	return (1);
}
