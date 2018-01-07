/*
** EPITECH PROJECT, 2017
** double_to_str
** File description:
** returns a float with a given decimals number as string
*/

#include "my.h"
#include "functions.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

int	concat_dec_part(int dec_part, int decimals, char *str)
{
	int     dec_length = 0;
	int	decimal;
	char	*nbr = 0;

	if (dec_part < 0)
		dec_part *= -1;
	decimal = dec_part;
	do {
		decimal /= 10;
		dec_length++;
	} while (decimal > 0);
	for (int i = decimals - dec_length; i > 0; i--)
		strcat(str, "0");
        nbr = int_to_str(dec_part);
	strcat(str, nbr);
	free(nbr);
	return (0);
}

char	*double_to_str(double nbr)
{
	long	number;
	long 	exponant;
	int	neg = 1;
	char	*str = 0;
	char	*nbrs = 0;
	int	decimals = 10;

	if (nbr < 0)
		neg *= -1;
	exponant = (long)pow(10, decimals);
	number = (long)(exponant * nbr + 0.5 * neg);
	str = malloc(get_nbrlen(number) + decimals + 2);
        nbrs = int_to_str((int)(number / exponant));
	strcpy(str, nbrs);
	free(nbrs);
	strcat(str, ".");
	concat_dec_part(number % exponant, decimals, str);
	return (str);
}
