/*
** EPITECH PROJECT, 2017
** my_strlen_rec
** File description:
** give the length of a string in recursive
*/

int	my_strlen_rec(char const *str)
{
	int length = 0;

	if (*str == 0)
		return (0);
	length = my_strlen_rec(str + 1) + 1;
	return (length);
}
