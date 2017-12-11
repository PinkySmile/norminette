/*
** EPITECH PROJECT, 2017
** my_compute_power_rec
** File description:
** Power of n
*/

int	my_compute_power_rec(int nb, int p)
{
	if (p > 0)
		nb *= my_compute_power_rec(nb, p - 1);
	else
		return (1);
	return (nb);
}
