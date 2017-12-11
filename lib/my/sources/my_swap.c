/*
** EPITECH PROJECT, 2017
** my_swap
** File description:
** swaps 2 values at 2 given addresses
*/

void	 my_swap(int *a, int *b)
{
	int  buffer = 0;

	buffer = *a;
	*a = *b;
	*b = buffer;
}
