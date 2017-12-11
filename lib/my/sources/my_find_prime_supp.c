/*
** EPITECH PROJECT, 2017
** my_find_prime_sup
** File description:
** Find the smallest prime nb greater than the one given
*/

#include "my.h"

int my_find_prime_sup(int nb)
{
	int result = nb;

	while (my_is_prime(result) == 0)
		result++;
	return (result);
}
