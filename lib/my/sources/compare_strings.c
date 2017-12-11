/*
** EPITECH PROJECT, 2017
** compare_strings.c
** File description:
** Compare to strings return 1 if same or 0
*/

int	compare_strings(char *str1, char *str2)
{
	if (my_str_len(str1) != my_str_len(str2))
		return (0);
	for (int i = 0; i < my_str_len(str1); i++)
		if (str1[i] != str2[i])
			return (0);
	return (1);
}
