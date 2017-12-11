/*
** EPITECH PROJECT, 2017
** my_str_isupper
** File description:
** return 1 if only CAPS are in the string
*/

int	my_str_isupper(char const *str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] < 'A' && str[i] > 'Z')
			return (0);
	return (1);
}
