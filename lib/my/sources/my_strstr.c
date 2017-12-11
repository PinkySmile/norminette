/*
** EPITECH PROJECT, 2017
** my_strstr
** File description:
** Find a string in another
*/

#include "my.h"

char	*sub_strings(char const *str, int start, int end, char *to_return)
{
	int pos = start > 0 ? -start : 0;
	int i = start > 0 ? start : 0;
	int real_start = i;

        for (; i < end && str[i]; i++) {
		to_return[pos + i] = str[i];
	}
        to_return[i - real_start] = 0;
	return (to_return);
}

int     compare_strings(char const *str1, char const *str2)
{
	if (my_strlen(str1) != my_strlen(str2))
		return (0);
	for (int i = 0; i < my_strlen(str1); i++)
		if (str1[i] != str2[i])
			return (0);
	return (1);
}

char	*my_strstr(char *str, char const *to_find)
{
	int	str_length;
	int	to_find_length;
	int	cond;
	char	storage[my_strlen(str) + 1];

	str_length = my_strlen(str);
	to_find_length = my_strlen(to_find);
	for (int i = 0; i + to_find_length <= str_length; i++) {
		sub_strings(str, i, i + to_find_length, storage);
		if (compare_strings(storage, to_find))
			return (str + i);
	}
	return (str);
}
