/*
** EPITECH PROJECT, 2017
** get_nbrlen
** File description:
** Returns the length of the number in characters
*/

int	get_nbrlen(long long nbr)
{
	int i = 0;

	if (nbr < 0) {
		nbr *= -1;
		i++;
	}
	do {
		i++;
		nbr /= 10;
	} while (nbr > 0);
	return (i);
}
