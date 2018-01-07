/*
** EPITECH PROJECT, 2018
** get_nbrlen
** File description:
** Get the length of a number in characters
*/

#include "functions.h"

int	get_nbrlen(int nbr)
{
	int	len = 0;

	do {
		nbr /= 10;
		len++;
	} while (nbr > 0);
	return (len);
}
