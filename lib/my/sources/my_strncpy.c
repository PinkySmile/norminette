/*
** EPITECH PROJECT, 2017
** my_strncpy
** File description:
** Copy n chars of a string into another
*/

char	*my_strncpy(char *dest, char const *src, int n)
{
	for (int i = 0; i < n - 1; i++) {
		dest[i] = src[i];
	}
	dest[n] = '\0';
	return (dest);
}
