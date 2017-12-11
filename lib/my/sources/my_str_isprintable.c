/*
** EPITECH PROJECT, 2017
** my_str_isprintable
** File description:
** Return 1 if the string contains only printable chars
*/

int	my_str_isprintable(char const *str)
{
	for (int i = 0; i != '\0'; i++)
		if (str[i] < 32 || str[i] > 176)
			return (0);
	return (1);
}
