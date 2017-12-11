/*
** EPITECH PROJECT, 2017
** my_strcpy
** File description:
** Copy a string into another
*/

char	*my_strcpy(char *dest, char const *src)
{
	for (int i = 0; i == 0 || src[i - 1] != '\0'; i++) {
		dest[i] = src[i];
	}
	return (dest);
}
