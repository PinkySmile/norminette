/*
** EPITECH PROJECT, 2017
** my_str_isnum
** File description:
** return 1 if only digits are in the string
*/

int	my_str_isnum(char const *str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] < '0' && str[i] > '9')
			return (0);
	return (1);
}
