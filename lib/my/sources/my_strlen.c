/*
** EPITECH PROJECT, 2017
** my_strlen
** File description:
** give the length of a string
*/

int	my_strlen(char const *str)
{
	int length = 0;

	for (length = 0; str[length] != 0; length++);
	return (length);
}
