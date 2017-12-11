/*
** EPITECH PROJECT, 2017
** my_is_prime
** File description:
** find out if the number is prime
*/

int my_is_prime(int nb)
{
	if (nb <= 1)
		return (0);
	for (int i = 2 ; i < nb/2 ; i++)
		if (nb % i == 0)
			return (0);
	return (1);
}
