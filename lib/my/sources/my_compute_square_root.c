/*
** EPITECH PROJECT, 2017
** my_compute_square_root
** File description:
** Square root of a number
*/

#include "my.h"

int my_compute_square_root(int nb)
{
	int number = 0;

	while (my_compute_power_rec(number, 2) < nb) {
		number++;
	}
	return (number);
}
