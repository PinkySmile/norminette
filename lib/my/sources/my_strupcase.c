/*
** EPITECH PROJECT, 2017
** my_strupcase
** File description:
** puts a string in CAPS
*/

char	*my_strupcase(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 'a' + 'A';
	return (str);
}
