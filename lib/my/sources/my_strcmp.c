/*
** EPITECH PROJECT, 2017
** my_strcmp
** File description:
** compare two strings and returns the number of differences
*/

int	my_strcmp(char const *s1, char const *s2)
{
	int	i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
